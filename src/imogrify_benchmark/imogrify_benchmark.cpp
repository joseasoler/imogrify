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
#include <imfy/build.hpp>
#include <imfy/character_encoding.hpp>
#include <imfy/filesystem.hpp>
#include <imfy/image_format.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <fmt/base.h>
#include <fmt/format.h>
#include <tl/expected.hpp>

#include <array>
#include <cstdlib>
#include <exception>
#include <optional>

namespace
{
tl::expected<std::optional<imfy::fs::path_view>, imfy::string> get_output_path(const int argc, char** argv)
{
	if (argc > 1)
	{
		using namespace imfy::fs;
		const path_view directory{argv[1U]};
		if (const auto result = create_directories(directory); !result.has_value())
		{
			const auto description = error_description(result.error());
			return tl::unexpected{fmt::format("Could not create output directory {:s}: {:s}", directory, description)};
		}

		return directory;
	}

	return {};
}

}

int main(const int argc, char** argv)
{
	try
	{
		if (const auto encoding_result = imfy::character_encoding::initialize(); !encoding_result)
		{
			fmt::print("{:s}", encoding_result.error());
			return EXIT_FAILURE;
		}

		using namespace imfy::bench;

		const auto output_path_result = get_output_path(argc, argv);
		if (!output_path_result)
		{
			fmt::print("{:s}", output_path_result.error());
			return EXIT_FAILURE;
		}

		const auto& output_path = output_path_result.value();

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
				 .compression = imfy::image::compression_t::standard},
				{.format = format_t::png,
				 .operation = operation_t::encode,
				 .libraries = {library_t::libpng, library_t::lodepng, library_t::spng},
				 .channels = imfy::image::channel_t::four,
				 .bit_depth = imfy::image::bit_depth_t::eight,
				 .image_gen = image_gen_t::modulo,
				 .size = size_gen_t::large,
				 .compression = imfy::image::compression_t::standard},
		};

		const auto image_result{generate_benchmark_images(definitions, output_path)};
		if (!image_result.has_value())
		{
			if (output_path.has_value())
			{
				fmt::println("Could not save reference images at {:s}: {:s}", output_path.value(), image_result.error());
			}
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
	catch (const std::exception& exc)
	{
		fmt::println("{:s} has been terminated because of an exception: {:s}", imfy::build::project.name, exc.what());
		return EXIT_FAILURE;
	}
	catch (...)
	{
		fmt::println("{:s} has been terminated because of an unknown exception", imfy::build::project.name);
		return EXIT_FAILURE;
	}
}
