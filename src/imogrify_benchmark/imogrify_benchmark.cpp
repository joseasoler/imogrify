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

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstdlib>
#include <string_view>

namespace
{

using imfy::bench::definition;
using imfy::bench::format_def;
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
				.size = size_def::large,
				.compression = static_cast<std::int32_t>(imfy::png::default_compression)
		},
};

} // namespace

int main(int /*argc*/, char** /*argv*/) // NOLINT
{
	if (!imfy::set_terminal())
	{
		std::cerr << "Could not configure terminal output.\n";
		return EXIT_FAILURE;
	}

	using namespace imfy::bench;

	// ToDo CLI arguments parsing.
	constexpr std::string_view hardcoded_output_path{"."};
	constexpr std::array renderers{renderer::markdown};
	imfy::vector<definition> sorted_definitions(definitions.cbegin(), definitions.cend());
	std::sort(sorted_definitions.begin(), sorted_definitions.end());

	const imfy::bench::benchmark_images images(definitions, hardcoded_output_path);
	benchmark_execution execution(images);
	benchmark_output output(hardcoded_output_path, renderers);

	for (const auto& def : sorted_definitions)
	{
		const result res = execution.run(def);
		output.output(res);
	}

	return EXIT_SUCCESS;
}
