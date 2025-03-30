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
#include <imfy/character_encoding.hpp>
#include <imfy/image_format.hpp>
#include <imfy/vector.hpp>

#include <optional>

#if IMOGRIFY_USE_FMT_BASE_HEADER
#include <fmt/base.h>
#else
// Older versions of fmt lack the fmt/base.h header.
#include <fmt/ostream.h>
#endif // #if IMOGRIFY_USE_FMT_BASE_HEADER

#include <array>
#include <cstdlib>
#include <filesystem>
#include <string_view>

// NOLINTNEXTLINE(bugprone-exception-escape)
int main(int argc, char** argv)
{
	if (const auto encoding_result = imfy::character_encoding::initialize(); !encoding_result)
	{
		fmt::print("{}", encoding_result.error());
		return EXIT_FAILURE;
	}

	using namespace imfy::bench;

	const bool has_output_path = argc > 1;
	const std::string_view output_path_view = has_output_path ? argv[1U] : std::string_view{};
	std::optional<std::filesystem::path> output_path{};
	if (has_output_path)
	{
		output_path = output_path_view;
	}

	if (has_output_path && !is_directory(output_path.value()))
	{
		fmt::println("{:s} must be a valid directory.", output_path_view);
		return EXIT_FAILURE;
	}

	// ToDo CLI arguments parsing and validation.
	constexpr std::array renderers{renderer::markdown};

	const imfy::vector<definition> definitions{
			{.format = format_t::png,
			 .operation = operation_t::encode,
			 .libraries = {library_t::libpng, library_t::lodepng, library_t::spng},
			 .channels = imfy::image::channel_t::four,
			 .bit_depth = imfy::image::bit_depth_t::eight,
			 .image_gen = image_gen_t::modulo,
			 .size = size_gen_t::small,
			 .compression = imfy::image::compression_t::best},
	};
	const auto image_result{generate_benchmark_images(definitions, output_path)};
	if (!image_result.has_value())
	{
		fmt::println("Could not save reference images at {:s}: {:s}", output_path_view, image_result.error());
		return EXIT_FAILURE;
	}
	const auto& images = image_result.value();
	benchmark_execution execution{};
	// ToDo CLI arguments parsing and validation.
	benchmark_output output{renderers};

	for (const auto& def : definitions)
	{
		const result res = execution.run(def, images);
		output.output(res);
	}

	return EXIT_SUCCESS;
}
