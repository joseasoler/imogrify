/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_execution.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_output.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/encoding.hpp>
#include <imfy/vector.hpp>

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

int main(int argc, char** argv) // NOLINT
{
	if (!imfy::initialize_encoding())
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

	imfy::vector<definition> definitions{};
	const benchmark_images images(definitions);
	benchmark_execution execution(images);
	// ToDo CLI arguments parsing and validation.
	benchmark_output output(output_path, renderers);

	if (has_output_path && !images.save_all(output_path))
	{
		fmt::println("Could not save reference images at {:s}.", output_path_view);
		return EXIT_FAILURE;
	}
	for (const auto& def : definitions)
	{
		const result res = execution.run(def);
		output.output(res);
	}

	return EXIT_SUCCESS;
}
