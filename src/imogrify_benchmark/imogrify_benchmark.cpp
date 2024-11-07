/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_execution.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_output.hpp>
#include <imfy/benchmark_parameters.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/encoding.hpp>
#include <imfy/png_format.hpp>
#include <imfy/vector.hpp>

#if IMOGRIFY_USE_FMT_BASE_HEADER
#include <fmt/base.h>
#else
// Older versions of fmt lack the fmt/base.h header.
#include <fmt/ostream.h>
#endif // #if IMOGRIFY_USE_FMT_BASE_HEADER

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <filesystem>
#include <string_view>

namespace
{

using imfy::bench::definition;
using imfy::bench::format_def;
using imfy::bench::image_gen_def;
using imfy::bench::library_flags;
using imfy::bench::operation_def;
using imfy::bench::size_def;

constexpr auto png_encode_libs = library_flags::libspng | library_flags::libpng | library_flags::lodepng;

constexpr std::array definitions{
		definition{
				.format = format_def::png,
				.operation = operation_def::encode,
				.libraries = png_encode_libs,
				.channels = 4U,
				.bit_depth = 8U,
				.image_gen = image_gen_def::mod,
				.size = size_def::large,
				.compression = static_cast<std::int32_t>(imfy::png::default_compression)
		},
		definition{
				.format = format_def::png,
				.operation = operation_def::encode,
				.libraries = png_encode_libs,
				.channels = 4U,
				.bit_depth = 8U,
				.image_gen = image_gen_def::rnd,
				.size = size_def::large,
				.compression = static_cast<std::int32_t>(imfy::png::default_compression)
		},
};

} // namespace

int main(int argc, char** argv) // NOLINT
{
	if (!imfy::set_terminal())
	{
		fmt::println("Could not configure terminal output.");
		return EXIT_FAILURE;
	}

	using namespace imfy::bench;

	const bool has_output_path = argc > 1;
	const std::string_view output_path_view = has_output_path ? argv[1U] : std::string_view{};
	const std::filesystem::path output_path{output_path_view};
	if (has_output_path && !std::filesystem::is_directory(output_path))
	{
		fmt::println("{:s} must be a valid directory.", output_path_view);
		return EXIT_FAILURE;
	}

	// ToDo CLI arguments parsing and validation.
	constexpr std::array renderers{renderer::markdown};

	imfy::vector<definition> sorted_definitions(definitions.cbegin(), definitions.cend());
	std::sort(sorted_definitions.begin(), sorted_definitions.end());

	const imfy::bench::benchmark_images images(definitions);
	benchmark_execution execution(images);
	// ToDo CLI arguments parsing and validation.
	benchmark_output output(output_path, renderers);

	if (has_output_path && !images.save_all(output_path))
	{
		fmt::println("Could not save reference images at {:s}.", output_path_view);
		return EXIT_FAILURE;
	}
	for (const auto& def : sorted_definitions)
	{
		const result res = execution.run(def);
		output.output(res);
	}

	return EXIT_SUCCESS;
}
