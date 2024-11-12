/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_size.hpp>
#include <imfy/vector.hpp>

#include <cstdint>

namespace imfy::bench
{

enum class format_t : std::uint8_t
{
	png,
};

/** Determines how the reference image is generated. */
enum class image_gen_t : std::uint8_t
{
	// All pixels are set to zero.
	zero,
	// Adjacent pixels are different, but the same colors are repeated frequently on the image.
	modulo,
	// Pixel colors are entirely random.
	random,
};

enum class operation_t : std::uint8_t
{
	encode,
	decode
};

enum class library_t : std::uint8_t
{
	libpng,
	lodepng,
	spng,
};

enum class size_gen_t : std::uint8_t
{
	small,
	large,
	tall,
	wide
};

} // namespace imfy::bench