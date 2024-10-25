/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark.hpp"

#include <imfy/markdown.hpp>

#include <array>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <ratio>
#include <string_view>

#include <nanobench.h>

namespace
{
constexpr auto nanosecond_count = std::chrono::duration<double>{std::chrono::nanoseconds{1}}.count();
using nanosecond_t = std::chrono::duration<std::uint64_t, std::nano>;

#if ANKERL_NANOBENCH(PERF_COUNTERS)
constexpr std::size_t bench_cell_count = 12U;
#else
constexpr std::size_t bench_cell_count = 8U;
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)

constexpr std::array<std::string_view, bench_cell_count> bench_table_header{
		"Library",			"Channels", "Bit depth", "Width",		 "Height", "Bytes", "Time (ns)", "Error",
#if ANKERL_NANOBENCH(PERF_COUNTERS)
		"Instructions", "Cycles",		"Branches",	 "B. Misses"
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
};

consteval std::array<std::uint8_t, bench_cell_count> get_bench_cell_width()
{
	constexpr std::array<std::uint8_t, bench_cell_count> data_width{
			8U,
			4U,
			2U,
			std::numeric_limits<std::uint16_t>::digits10,
			std::numeric_limits<std::uint16_t>::digits10,
			15U,
			10U,
			10U,
#if ANKERL_NANOBENCH(PERF_COUNTERS)
			10U,
			10U,
			10U,
			10U
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
	};

	return imfy::get_cell_width(data_width, bench_table_header);
}

constexpr std::array<std::uint8_t, bench_cell_count> bench_cell_width = get_bench_cell_width();

std::uint64_t round_to_uint64_t(const double value)
{
	return static_cast<std::uint64_t>(std::round(value));
}

} // Anonymous namespace

namespace imfy
{
void render_start_table(imfy::markdown& mark)
{
	mark.add_table_header(bench_cell_width, bench_table_header);
}

void render_benchmark_row(
		const std::string_view library, const std::string_view channels, const std::uint8_t bit_depth,
		const std::uint16_t width, const std::uint16_t height, const std::size_t file_size,
		const ankerl::nanobench::Result& data, imfy::markdown& mark
)
{
	mark.add_table_cell(bench_cell_width[0U], library);
	mark.add_table_cell(bench_cell_width[1U], channels);
	mark.add_table_unsigned(bench_cell_width[2U], bit_depth);
	mark.add_table_unsigned(bench_cell_width[3U], width);
	mark.add_table_unsigned(bench_cell_width[4U], height);
	mark.add_table_unsigned(bench_cell_width[5U], file_size);

	using measure = ankerl::nanobench::Result::Measure;
	mark.add_table_unsigned(
			bench_cell_width[6U], nanosecond_t{round_to_uint64_t(data.median(measure::elapsed) / nanosecond_count)}.count()
	);
	mark.add_table_percent(bench_cell_width[7U], data.medianAbsolutePercentError(measure::elapsed) * 100.0);

#if ANKERL_NANOBENCH(PERF_COUNTERS)
	mark.add_table_unsigned(bench_cell_width[8U], round_to_uint64_t(data.median(measure::instructions)));
	mark.add_table_unsigned(bench_cell_width[9U], round_to_uint64_t(data.median(measure::cpucycles)));
	mark.add_table_unsigned(bench_cell_width[10U], round_to_uint64_t(data.median(measure::branchinstructions)));
	mark.add_table_unsigned(bench_cell_width[11U], round_to_uint64_t(data.median(measure::branchmisses)));
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
	mark.end_table_row();
}

void render_end_table(imfy::markdown& mark)
{
	mark.end_table();
}

} // namespace imfy
