/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/benchmark.hpp>
#include <imfy/markdown.hpp>
#include <imfy/png_benchmark.hpp>
#include <imfy/png_format.hpp>

#include <cstdlib>
#include <iostream>

#include <nanobench.h>

int main(int /*argc*/, char** /*argv*/) // NOLINT
{
	ankerl::nanobench::Bench bench{};
#if ANKERL_NANOBENCH(PERF_COUNTERS)
	// Enable performance counters feature when possible.
	bench.performanceCounters(true);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
	// Disable nanobench rendering.
	bench.output(nullptr);

	using imfy::markdown;
	markdown mark{std::cout};

	mark.add_heading(markdown::heading::level_1, "Library benchmarks");
	// ToDo build information
	// ToDo system information
	mark.add_heading(markdown::heading::level_3, "PNG");
	// ToDo library metadata.
	mark.add_heading(markdown::heading::level_4, "Encoding comparison");
	using namespace imfy::png;

	imfy::render_start_table(mark);
	using imfy::encode_png_benchmark;
	constexpr std::size_t test_size = 256U;

	encode_png_benchmark<color_type::gray, 8U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::gray, 16U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::ga, 8U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::ga, 16U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::rgb, 8U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::rgb, 16U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::rgba, 8U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	encode_png_benchmark<color_type::rgba, 16U>(bench, mark, test_size, test_size, imfy::png::default_compression);
	imfy::render_end_table(mark);

	return EXIT_SUCCESS;
}
