/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_format.hpp"

#include <imfy/image_format.hpp>

#include <png.h>

#include <zlib.h>

#include <doctest/doctest.h>

using namespace imfy::png;
using namespace imfy::image;

TEST_CASE("Definition of color_t")
{
	static_assert(static_cast<int>(color_t::gray) == PNG_COLOR_TYPE_GRAY);
	static_assert(static_cast<int>(color_t::rgb) == PNG_COLOR_TYPE_RGB);
	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	static_assert(static_cast<int>(color_t::palette) == PNG_COLOR_TYPE_PALETTE);
	static_assert(static_cast<int>(color_t::ga) == PNG_COLOR_TYPE_GA);
	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	static_assert(static_cast<int>(color_t::rgba) == PNG_COLOR_TYPE_RGBA);
}

TEST_CASE("Conversion of compression_t to zlib compression levels.")
{
	static_assert(to_png_compression(compression_t::none) == Z_NO_COMPRESSION);
	static_assert(to_png_compression(compression_t::speed) == Z_BEST_SPEED);
	constexpr int zlib_standard_compression = 6;
	static_assert(to_png_compression(compression_t::standard) == zlib_standard_compression);
	static_assert(to_png_compression(compression_t::best) == Z_BEST_COMPRESSION);
}

TEST_CASE("Conversion of channels_t to PNG color types.")
{
	static_assert(to_color_type(channel_t::one) == color_t::gray);
	static_assert(to_color_type(channel_t::two) == color_t::ga);
	static_assert(to_color_type(channel_t::three) == color_t::rgb);
	static_assert(to_color_type(channel_t::four) == color_t::rgba);
}
