/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_size.hpp>
#include <imfy/vector.hpp>

#include <compare>
#include <cstdint>
#include <type_traits>

namespace imfy::bench
{

/** Determines how the reference image is generated. */
enum class image_gen_def : std::uint8_t
{
	// Adjacent pixels are different, but the same colors are repeated frequently on the image.
	mod,
	// Pixel colors are entirely random.
	random,
	// Total number of image generators.
	count,
};

enum class format_def : std::uint8_t
{
	png,
};

enum class operation_def : std::uint8_t
{
	encode,
	decode
};

enum class library_flags : std::uint8_t
{
	libpng = 1U << 0U,
	libspng = 1U << 1U,
	lodepng = 1U << 2U,
};

constexpr library_flags operator|(library_flags lhs, library_flags rhs)
{
	using underlying_t = std::underlying_type_t<library_flags>;
	return static_cast<library_flags>(static_cast<underlying_t>(lhs) | static_cast<underlying_t>(rhs));
}

constexpr bool has_flag(library_flags value, library_flags flag)
{
	using underlying_t = std::underlying_type_t<library_flags>;
	return (static_cast<underlying_t>(value) & static_cast<underlying_t>(flag)) != 0U;
}

enum class size_def : std::uint8_t
{
	small,
	large,
	tall,
	wide
};

} // namespace imfy::bench