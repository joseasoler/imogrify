/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_encode_lodepng.hpp"

#include <imfy/png_format.hpp>

#include <lodepng.h>

#include <cstdint>
#include <cstdlib>
#include <span>

namespace
{
using imfy::png::color_type;
static_assert(static_cast<int>(color_type::gray) == LodePNGColorType::LCT_GREY);
static_assert(static_cast<int>(color_type::ga) == LodePNGColorType::LCT_GREY_ALPHA);
static_assert(static_cast<int>(color_type::palette) == LodePNGColorType::LCT_PALETTE);
static_assert(static_cast<int>(color_type::rgb) == LodePNGColorType::LCT_RGB);
static_assert(static_cast<int>(color_type::rgba) == LodePNGColorType::LCT_RGBA);
} // namespace

namespace imfy
{

std::size_t encode_lodepng(
		imfy::png::color_type color, std::uint8_t bit_depth, std::uint32_t width, std::uint32_t height,
		std::span<const std::uint8_t> input_image, std::uint8_t /*compression_level*/
)
{
	unsigned char* png{};
	std::size_t png_size{};
	LodePNGState state;

	lodepng_state_init(&state);
	state.info_raw.colortype = static_cast<LodePNGColorType>(color);
	state.info_raw.bitdepth = bit_depth;
	state.info_png.color.colortype = static_cast<LodePNGColorType>(color);
	state.info_png.color.bitdepth = bit_depth;

	auto error = lodepng_encode(&png, &png_size, input_image.data(), width, height, &state);
	if (error != 0U) [[unlikely]]
	{
		std::abort();
	}

	lodepng_state_cleanup(&state);

	// NOLINTNEXTLINE(cppcoreguidelines-no-malloc, hicpp-no-malloc)
	std::free(png);

	return png_size;
}

} // namespace imfy