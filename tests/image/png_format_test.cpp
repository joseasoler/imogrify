/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_format.hpp"

#include <png.h>

#include <zlib.h>

#include <doctest/doctest.h>

TEST_CASE("color_type")
{
	using imfy::png::color_type;
	static_assert(static_cast<int>(color_type::gray) == PNG_COLOR_TYPE_GRAY);
	static_assert(static_cast<int>(color_type::rgb) == PNG_COLOR_TYPE_RGB);
	static_assert(static_cast<int>(color_type::palette) == PNG_COLOR_TYPE_PALETTE);
	static_assert(static_cast<int>(color_type::ga) == PNG_COLOR_TYPE_GA);
	static_assert(static_cast<int>(color_type::rgba) == PNG_COLOR_TYPE_RGBA);
}

TEST_CASE("compression level")
{
	using namespace imfy::png;

	static_assert(no_compression == Z_NO_COMPRESSION);
	static_assert(speed_compression == Z_BEST_SPEED);
	static_assert(default_compression == 6); // Check the zlib documentation for details.
	static_assert(best_compression == Z_BEST_COMPRESSION);
}