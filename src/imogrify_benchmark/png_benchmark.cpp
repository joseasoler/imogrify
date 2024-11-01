/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_benchmark.hpp"

#include <imfy/benchmark.hpp>
#include <imfy/image_size.hpp>
#include <imfy/markdown.hpp>
#include <imfy/png_encoder.hpp>
#include <imfy/png_format.hpp>
#include <imfy/png_lodepng.hpp>
#include <imfy/png_spng.hpp>
#include <imfy/raw_image.hpp>

#include <magic_enum.hpp>

#include <array>
#include <cstddef>
#include <cstdint>

#include <nanobench.h>

namespace imfy
{

namespace detail
{

std::uint8_t channels_per_color_type(imfy::png::color_type color_type)
{
	switch (color_type)
	{
		case color_type::gray:
			return 1U;
		case color_type::ga:
			return 2U;
		case color_type::palette:
			return 1U;
		case color_type::rgb:
			return 3U;
		case color_type::rgba:
			return 4U;
	}

	return 4U;
}

raw_image get_initialized_image(std::uint8_t channels, std::uint8_t bit_depth, image_size img_size)
{
	imfy::raw_image image(channels, bit_depth, img_size);
	constexpr std::array<std::uint8_t, 4U> byte_modulo{251U, 241U, 239U, 233U};

	std::size_t value_index{0U};
	auto* data_ptr = image.data().as_writable_bytes().data();
	const auto* data_cend = data_ptr + image.data().size_bytes();
	for (; data_ptr != data_cend; ++data_ptr, ++value_index)
	{
		*data_ptr = static_cast<std::uint8_t>(value_index % byte_modulo[value_index % 4U]);
	}

	return image;
}

} // namespace detail

void benchmark_png_encoding(
		ankerl::nanobench::Bench& bench, imfy::markdown& mark, imfy::png::color_type color_type, std::uint8_t bit_depth,
		imfy::image_size img_size, std::uint8_t compression_level
)
{
	const auto channels = detail::channels_per_color_type(color_type);
	const auto channels_str = magic_enum::enum_name(color_type);
	const raw_image test_image = detail::get_initialized_image(channels, bit_depth, img_size);
	const auto raw_data_span = test_image.data();

	run_benchmark(
			bench, mark, "libpng", channels_str, bit_depth, img_size,
			[&]() -> std::size_t
			{
				const auto result = imfy::png::encode(color_type, bit_depth, img_size, raw_data_span, compression_level);
				return result.has_value() ? result.value().size() : 0U;
			}
	);

	run_benchmark(
			bench, mark, "lodepng", channels_str, bit_depth, img_size,
			[&]() -> std::size_t { return encode_lodepng(color_type, bit_depth, img_size, raw_data_span, compression_level); }
	);

	run_benchmark(
			bench, mark, "spng", channels_str, bit_depth, img_size,
			[&]() -> std::size_t { return encode_spng(color_type, bit_depth, img_size, raw_data_span, compression_level); }
	);
}

} // namespace imfy
