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

/** Image format being benchmarked. */
enum class format_def : std::uint8_t
{
	png,
};

/** Determines how the reference image is generated. */
enum class image_gen_def : std::uint8_t
{
	// All pixels are set to zero.
	zero,
	// Adjacent pixels are different, but the same colors are repeated frequently on the image.
	modulo,
	// Pixel colors are entirely random.
	random,
};

enum class operation_def : std::uint8_t
{
	encode,
	decode
};

enum class library_flags : std::uint8_t
{
	libpng = 1U << 0U,
	lodepng = 1U << 1U,
	spng = 1U << 2U,
};

enum class size_def : std::uint8_t
{
	small,
	large,
	tall,
	wide
};

} // namespace imfy::bench