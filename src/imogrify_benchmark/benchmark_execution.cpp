/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_execution.hpp"

#include <imfy/assert.hpp>
#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_parameters.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/image_format.hpp>
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

constexpr auto percent_factor = 100.0;

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
raw_library_result run_benchmark_impl(Bench& bench, const library_t library, const Operation& operation)
{
	raw_library_result run_result{};
	run_result.lib_res.library = library;
	bench.run([&file_size = run_result.file_size, &operation]() { file_size = operation(); });

	// Extract information from nanobench.
	using measure = ankerl::nanobench::Result::Measure;
	const ankerl::nanobench::Result& data = bench.results().back();

	constexpr auto to_milliseconds_factor = 1000000.0;
	run_result.lib_res.milliseconds =
			static_cast<double>(to_nanoseconds(data.median(measure::elapsed)).count()) / to_milliseconds_factor;
	run_result.lib_res.speed_error = data.medianAbsolutePercentError(measure::elapsed) * percent_factor;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
	run_result.lib_res.instructions = round_to_uint64_t(data.median(measure::instructions));
	run_result.lib_res.cycles = round_to_uint64_t(data.median(measure::cpucycles));
	run_result.lib_res.branch_instructions = round_to_uint64_t(data.median(measure::branchinstructions));
	run_result.lib_res.branch_misses = round_to_uint64_t(data.median(measure::branchmisses));
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)

	run_result.total_iterations = round_to_uint64_t(data.sum(measure::iterations));
	run_result.total_time = to_nanoseconds(data.sumProduct(measure::iterations, measure::elapsed));

	// Setting a new title forces a clear of internal nanobench results.
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
		constexpr auto to_kib_factor = 1024.0;
		lib_result.file_size = static_cast<double>(raw_lib_result.file_size) / to_kib_factor;
		lib_result.file_size_rel = percent_factor * static_cast<double>(raw_lib_result.file_size) / reference_file_size;
		lib_result.mpix_second = to_megapixels_per_second(pixels, raw_lib_result);
		lib_result.speed_relative = percent_factor * lib_result.mpix_second / reference_mpix_second;
		library_results.push_back(lib_result);
	}

	return library_results;
}

imfy::vector<raw_library_result> run_png_encode_benchmark(
		Bench& bench, const imfy::image::raw_image& image, const imfy::vector<library_t>& libraries,
		const imfy::image::compression_t compression
)
{
	imfy::vector<raw_library_result> results;
	const auto color = imfy::png::to_color_type(image.channels());

	for (const library_t library : libraries)
	{
		if (library == library_t::libpng)
		{
			results.push_back(run_benchmark_impl(
					bench, library,
					[&color, &image, &compression]() -> std::size_t
					{
						const auto result = encode(color, image.bit_depth(), image.size(), image.data(), compression);
						return result.has_value() ? result.value().size() : 0U;
					}
			));
		}
		else if (library == library_t::lodepng)
		{
			results.push_back(run_benchmark_impl(
					bench, library, [&color, &image, &compression]() -> std::size_t
					{ return encode_lodepng(color, image.bit_depth(), image.size(), image.data(), compression); }
			));
		}
		else if (library == library_t::spng)
		{
			results.push_back(run_benchmark_impl(
					bench, library, [&color, &image, &compression]() -> std::size_t
					{ return encode_spng(color, image.bit_depth(), image.size(), image.data(), compression); }
			));
		}
	}

	return results;
}

}

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
	const image::raw_image* image = images_.get(def);
	IMFY_ASSUME(image != nullptr);
	res.img_size = image->size();
	res.compression = def.compression;

	vector<raw_library_result> raw_library_results;
	if (def.format == format_t::png && def.operation == operation_t::encode)
	{
		raw_library_results = run_png_encode_benchmark(*bench_, *image, def.libraries, res.compression);
	}

	const auto pixels = static_cast<std::size_t>(image->size().width) * static_cast<std::size_t>(image->size().height);
	res.library_results = calculate_library_results(raw_library_results, pixels);
	return res;
}

}
