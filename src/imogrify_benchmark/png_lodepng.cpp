/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_lodepng.hpp"

#include <imfy/aligned_span.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>

#include <lodepng.h>

#include <cstdlib>

namespace
{
using namespace imfy::image;

/**
 * Maps the channel counts supported by imogrify to PNG color types. Ignores palette.
 * @param channels Channel count.
 * @return Color type.
 */
constexpr int to_color_type(const channel_t channels)
{
	using imfy::image::channel_t;
	switch (channels)
	{
		case channel_t::one:
			return LCT_GREY;
		case channel_t::two:
			return LCT_GREY_ALPHA;
		case channel_t::three:
			return LCT_RGB;
		default:
			[[fallthrough]];
		case channel_t::four:
			return LCT_RGBA;
	}
}

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

std::size_t encode_lodepng(const raw_image& input_image, const compression_t compression_level)
{
	LodePNGState state{};

	lodepng_state_init(&state);
	state.info_raw.colortype = static_cast<LodePNGColorType>(to_color_type(input_image.channels()));
	state.info_raw.bitdepth = static_cast<unsigned int>(input_image.bit_depth());
	state.info_png.color.colortype = state.info_raw.colortype;
	state.info_png.color.bitdepth = static_cast<unsigned int>(input_image.bit_depth());
	state.encoder.zlibsettings = get_compression_settings(compression_level);

	unsigned char* png{};
	std::size_t png_size{};
	const auto error = lodepng_encode(
			&png, &png_size, input_image.data().data(), input_image.size().width, input_image.size().height, &state
	);
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
