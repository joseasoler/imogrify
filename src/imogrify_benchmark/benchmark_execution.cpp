/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_execution.hpp"

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_parameters.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/png_format.hpp>
#include <imfy/png_lodepng.hpp>
#include <imfy/png_spng.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/vector.hpp>

#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <ratio>
#include <type_traits>

#include "imfy/png_encoder.hpp"

#include <nanobench.h>

namespace
{
using namespace imfy::bench;
using ankerl::nanobench::Bench;

std::unique_ptr<Bench> initialize_nanobench()
{
	auto bench = std::make_unique<Bench>();
#if ANKERL_NANOBENCH(PERF_COUNTERS)
	// Enable performance counters feature when possible.
	bench->performanceCounters(true);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
	// Disable nanobench rendering.
	bench->output(nullptr);

	return bench;
}

std::uint64_t round_to_uint64_t(const double value)
{
	return static_cast<std::uint64_t>(std::round(value));
}

using nanosecond_t = std::chrono::duration<std::uint64_t, std::nano>;

nanosecond_t to_nanoseconds(const double value)
{
	constexpr auto nanosecond_count = std::chrono::duration<double>{std::chrono::nanoseconds{1}}.count();
	return nanosecond_t{round_to_uint64_t(value / nanosecond_count)};
}

template <typename Operation>
concept benchmark_operation = std::is_same_v<std::invoke_result_t<Operation>, std::size_t>;

struct raw_library_result final
{
	library_result lib_res;
	std::size_t file_size;
	std::uint64_t total_iterations;
	nanosecond_t total_time;
};

template <benchmark_operation Operation>
raw_library_result run_benchmark_impl(Bench& bench, const library_flags library, const Operation& operation)
{
	raw_library_result run_result{};
	run_result.lib_res.library = library;
	bench.run([&file_size = run_result.file_size, &operation]() { file_size = operation(); });

	// Extract information from nanobench.
	using measure = ankerl::nanobench::Result::Measure;
	const ankerl::nanobench::Result& data = bench.results().back();

	run_result.lib_res.speed_error = data.medianAbsolutePercentError(measure::elapsed) * 100.0;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
	run_result.lib_res.instructions = round_to_uint64_t(data.median(measure::instructions));
	run_result.lib_res.cycles = round_to_uint64_t(data.median(measure::cpucycles));
	run_result.lib_res.branch_instructions = round_to_uint64_t(data.median(measure::branchinstructions));
	run_result.lib_res.branch_misses = round_to_uint64_t(data.median(measure::branchmisses));
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)

	run_result.total_iterations = round_to_uint64_t(data.sum(measure::iterations));
	run_result.total_time = to_nanoseconds(data.sumProduct(measure::iterations, measure::elapsed));

	// Force clear of internal nanobench results.
	bench.title("");
	return run_result;
}

double to_megapixels_per_second(const std::size_t pixels, const raw_library_result& raw_lib_res)
{
	constexpr auto factor = 1000.0;
	return factor * static_cast<double>(pixels * raw_lib_res.total_iterations) /
				 static_cast<double>(raw_lib_res.total_time.count());
}

imfy::vector<library_result> calculate_library_results(
		imfy::vector<raw_library_result>& raw_library_results, const std::size_t pixels
)
{
	if (raw_library_results.empty())
	{
		return {};
	}

	const auto reference_file_size = static_cast<double>(raw_library_results[0].file_size);
	const auto reference_mpix_second = to_megapixels_per_second(pixels, raw_library_results[0]);

	imfy::vector<library_result> library_results;
	for (auto& raw_lib_result : raw_library_results)
	{
		auto& lib_result = raw_lib_result.lib_res;
		lib_result.file_size = static_cast<double>(raw_lib_result.file_size) / 1024.0;
		lib_result.file_size_rel = 100.0 * static_cast<double>(raw_lib_result.file_size) / reference_file_size;
		lib_result.mpix_second = to_megapixels_per_second(pixels, raw_lib_result);
		lib_result.speed_relative = 100.0 * lib_result.mpix_second / reference_mpix_second;
		library_results.push_back(lib_result);
	}

	return library_results;
}

constexpr bool has_flag(library_flags value, library_flags flag)
{
	using underlying_t = std::underlying_type_t<library_flags>;
	return (static_cast<underlying_t>(value) & static_cast<underlying_t>(flag)) != 0U;
}

imfy::vector<raw_library_result> run_png_encode_benchmark(
		Bench& bench, const imfy::raw_image& image, const library_flags libraries, const std::int32_t compression
)
{
	imfy::vector<raw_library_result> results;
	const auto color = imfy::png::color_type_from_channels(image.channels());
	const auto compression_level = static_cast<std::uint8_t>(compression);

	if (has_flag(libraries, library_flags::libpng))
	{
		results.push_back(run_benchmark_impl(
				bench, library_flags::libpng,
				[&color, &image, &compression_level]() -> std::size_t
				{
					const auto result =
							imfy::png::encode(color, image.bit_depth(), image.size(), image.data(), compression_level);
					return result.has_value() ? result.value().size : 0U;
				}
		));
	}
	if (has_flag(libraries, library_flags::lodepng))
	{
		results.push_back(run_benchmark_impl(
				bench, library_flags::lodepng, [&color, &image, &compression_level]() -> std::size_t
				{ return encode_lodepng(color, image.bit_depth(), image.size(), image.data(), compression_level); }
		));
	}
	if (has_flag(libraries, library_flags::spng))
	{
		results.push_back(run_benchmark_impl(
				bench, library_flags::spng, [&color, &image, &compression_level]() -> std::size_t
				{ return encode_spng(color, image.bit_depth(), image.size(), image.data(), compression_level); }
		));
	}

	return results;
}

} // namespace

namespace imfy::bench
{

benchmark_execution::benchmark_execution(const benchmark_images& images)
	: bench_(initialize_nanobench())
	, images_{images}
{
}

benchmark_execution::~benchmark_execution() = default;

result benchmark_execution::run(const definition& def)
{
	result res;
	res.format = def.format;
	res.operation = def.operation;
	res.channels = def.channels;
	res.bit_depth = def.bit_depth;
	res.image_gen = def.image_gen;
	const imfy::raw_image* image = images_.get(def);
	if (image == nullptr)
	{
		return {};
	}
	res.img_size = image->size();
	res.compression = def.compression;

	imfy::vector<raw_library_result> raw_library_results;
	if (def.format == format_def::png && def.operation == operation_def::encode)
	{
		raw_library_results = run_png_encode_benchmark(*bench_, *image, def.libraries, res.compression);
	}

	const auto pixels = static_cast<std::size_t>(image->size().width) * static_cast<std::size_t>(image->size().height);
	res.library_results = calculate_library_results(raw_library_results, pixels);
	return res;
}

} // namespace imfy::bench