/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/vector.hpp>

#include <cstdint>
#include <string_view>

namespace imfy::bench
{

enum class format_t : std::uint8_t
{
	png,
};

constexpr std::string_view format_string(const format_t format)
{
	switch (format)
	{
		case format_t::png:
			return "png";
	}
	return {};
}

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

constexpr std::string_view image_gen_string(const image_gen_t image_gen)
{
	switch (image_gen)
	{
		case image_gen_t::zero:
			return "zero";
		case image_gen_t::modulo:
			return "modulo";
		case image_gen_t::random:
			return "random";
	}
	return {};
}

enum class operation_t : std::uint8_t
{
	encode,
	decode
};

constexpr std::string_view operation_string(const operation_t operation)
{
	switch (operation)
	{
		case operation_t::encode:
			return "encode";
		case operation_t::decode:
			return "decode";
	}
	return {};
}

enum class library_t : std::uint8_t
{
	libpng,
	lodepng,
	spng,
};

constexpr std::string_view library_string(const library_t library)
{
	switch (library)
	{
		case library_t::libpng:
			return "libpng";
		case library_t::lodepng:
			return "lodepng";
		case library_t::spng:
			return "spng";
	}
	return {};
}

enum class size_gen_t : std::uint8_t
{
	small,
	large,
	tall,
	wide
};

}
