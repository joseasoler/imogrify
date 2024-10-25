/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark.hpp>
#include <imfy/markdown.hpp>
#include <imfy/png_encode_libpng.hpp>
#include <imfy/png_encode_lodepng.hpp>
#include <imfy/png_encode_spng.hpp>
#include <imfy/png_format.hpp>
#include <imfy/raw_image.hpp>

#include <magic_enum.hpp>

#include <cstdint>
#include <span>
#include <string_view>

#include <nanobench.h>

using imfy::png::color_type;

namespace imfy
{

namespace detail
{
consteval std::uint8_t channels_per_color_type(imfy::png::color_type color_type)
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
} // namespace detail

template <imfy::png::color_type color_type, std::uint8_t bit_depth>
void encode_png_benchmark(
		ankerl::nanobench::Bench& bench, imfy::markdown& mark, std::uint16_t width, std::uint16_t height,
		std::uint8_t compression_level
)
{
	constexpr auto channels = detail::channels_per_color_type(color_type);
	using raw_image_t = imfy::image::raw_image<channels, bit_depth>;
	constexpr auto channels_str = magic_enum::enum_name(color_type);
	const raw_image_t test_image(imfy::image::image_size(width, height), imfy::image::initialization::modulo);
	const std::span<const std::uint8_t> raw_data = test_image.raw_data();

	run_benchmark(
			bench, mark, "libpng", channels_str, test_image, [&](const raw_image_t& image) -> std::size_t
			{ return encode_libpng(color_type, bit_depth, image.width(), image.height(), raw_data, compression_level); }
	);

	run_benchmark(
			bench, mark, "lodepng", channels_str, test_image, [&](const raw_image_t& image) -> std::size_t
			{ return encode_lodepng(color_type, bit_depth, image.width(), image.height(), raw_data, compression_level); }
	);

	run_benchmark(
			bench, mark, "spng", channels_str, test_image, [&](const raw_image_t& image) -> std::size_t
			{ return encode_spng(color_type, bit_depth, image.width(), image.height(), raw_data, compression_level); }
	);
}

} // namespace imfy