/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_format.hpp>

#include <cstdint>

namespace imfy::png
{

/** See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR */
enum class color_t : std::uint8_t
{
	gray = 0U,
	rgb = 2U,
	palette = 3U,
	ga = 4U,
	rgba = 6U,
};

/**
 * Maps the imogrify representation of compressions to the levels used by libpng.
 * See https://www.zlib.net/manual.html
 * @param compression imogrify compression level.
 * @return zlib compression level.
 */
constexpr int to_png_compression(image::compression_t compression)
{
	constexpr int zlib_no_compression = 0;
	constexpr int zlib_speed_compression = 1;
	constexpr int zlib_standard_compression = 6;
	constexpr int zlib_best_compression = 9;
	switch (compression)
	{
		case image::compression_t::none:
			return zlib_no_compression;
		case image::compression_t::speed:
			return zlib_speed_compression;
		case image::compression_t::standard:
		default:
			return zlib_standard_compression;
		case image::compression_t::best:
			return zlib_best_compression;
	}
}

/**
 * Maps the channel counts supported by imogrify to PNG color types. Ignores palette.
 * @param channels Channel count.
 * @return Color type.
 */
constexpr color_t to_color_type(image::channel_t channels)
{
	switch (channels)
	{
		case image::channel_t::one:
			return color_t::gray;
		case image::channel_t::two:
			return color_t::ga;
		case image::channel_t::three:
			return color_t::rgb;
		default:
		case image::channel_t::four:
			return color_t::rgba;
	}
}

}
