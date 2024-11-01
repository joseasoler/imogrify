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

	mark.add_build_information(markdown::heading::level_2);

	// ToDo system information
	mark.add_heading(markdown::heading::level_2, "Benchmarks");

	mark.add_heading(markdown::heading::level_3, "PNG");
	// ToDo library metadata.
	mark.add_heading(markdown::heading::level_4, "Encoding comparison");
	using namespace imfy::png;

	imfy::render_start_table(mark);
	using imfy::benchmark_png_encoding;
	constexpr std::size_t test_size = 2048U;

	benchmark_png_encoding(bench, mark, color_type::rgba, 8U, {test_size, test_size}, imfy::png::default_compression);
	imfy::render_end_table(mark);

	mark.add_heading(markdown::heading::level_4, "Decoding comparison");

	return EXIT_SUCCESS;
}
