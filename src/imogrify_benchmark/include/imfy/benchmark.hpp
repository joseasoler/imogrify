/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/markdown.hpp>

#include <nanobench.h>

namespace imfy
{

void render_start_table(imfy::markdown& mark);
void render_benchmark_row(
		std::string_view library, std::string_view channels, std::uint8_t bit_depth, std::uint16_t width,
		std::uint16_t height, std::size_t file_size, const ankerl::nanobench::Result& data, imfy::markdown& mark
);
void render_end_table(imfy::markdown& mark);

template <typename RawImage, typename Operation>
void run_benchmark(
		ankerl::nanobench::Bench& bench, imfy::markdown& mark, std::string_view library, std::string_view channels,
		const RawImage& image, const Operation& operation
)
{
	std::size_t file_size{};
	bench.run([&image, &operation, &file_size] { file_size = operation(image); });
	render_benchmark_row(
			library, channels, RawImage::bit_depth, image.width(), image.height(), file_size, bench.results().back(), mark
	);
	// Force clear of internal nanobench results.
	bench.title("");
}

} // namespace imfy