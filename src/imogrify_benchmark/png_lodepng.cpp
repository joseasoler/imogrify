/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_lodepng.hpp"

#include <imfy/aligned_span.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/png_format.hpp>

#include <lodepng.h>

#include <cstdint>
#include <cstdlib>

namespace
{
using namespace imfy::image;
using namespace imfy::png;

static_assert(static_cast<int>(color_t::gray) == LCT_GREY);
static_assert(static_cast<int>(color_t::ga) == LCT_GREY_ALPHA);
static_assert(static_cast<int>(color_t::palette) == LCT_PALETTE);
static_assert(static_cast<int>(color_t::rgb) == LCT_RGB);
static_assert(static_cast<int>(color_t::rgba) == LCT_RGBA);

constexpr unsigned int default_window_size = 1U << 11U;
constexpr unsigned int best_window_size = 1U << 15U;
constexpr unsigned int default_nice_match = 128U;
constexpr unsigned int best_nice_match = 258U;

constexpr LodePNGCompressSettings get_compression_settings(const compression_t compression)
{
	// Default compression settings for lodepng.
	LodePNGCompressSettings settings{
			.btype = 2U,
			.use_lz77 = 1U,
			.windowsize = default_window_size,
			.minmatch = 3U,
			.nicematch = default_nice_match,
			.lazymatching = 1,
			.custom_zlib = nullptr,
			.custom_deflate = nullptr,
			.custom_context = nullptr
	};

	switch (compression)
	{
		case compression_t::none:
			settings.btype = 0U;
			settings.use_lz77 = 0U;
			[[fallthrough]];
		case compression_t::speed:
			settings.minmatch = 0U;
			settings.nicematch = 0U;
			settings.lazymatching = 0U;
			break;
		case compression_t::standard:
			break;
		case compression_t::best:
			settings.windowsize = best_window_size;
			settings.nicematch = best_nice_match;
			break;
	}
	return settings;
}

}

namespace imfy
{

std::size_t encode_lodepng(
		const color_t color, const bit_depth_t bit_depth, const image_size img_size,
		const aligned_span<const std::uint8_t> input_image, const compression_t compression
)
{
	unsigned char* png{};
	std::size_t png_size{};
	LodePNGState state;

	lodepng_state_init(&state);
	state.info_raw.colortype = static_cast<LodePNGColorType>(color);
	state.info_raw.bitdepth = static_cast<unsigned int>(bit_depth);
	state.info_png.color.colortype = static_cast<LodePNGColorType>(color);
	state.info_png.color.bitdepth = static_cast<unsigned int>(bit_depth);
	state.encoder.zlibsettings = get_compression_settings(compression);

	auto error = lodepng_encode(&png, &png_size, input_image.data(), img_size.width, img_size.height, &state);
	if (error != 0U) [[unlikely]]
	{
		std::abort();
	}

	lodepng_state_cleanup(&state);

	// NOLINTNEXTLINE(hicpp-no-malloc)
	std::free(png);

	return png_size;
}

}
