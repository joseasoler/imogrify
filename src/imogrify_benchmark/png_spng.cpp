/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_spng.hpp"

#include <imfy/aligned_span.hpp>
#include <imfy/attributes.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>

#include <spng.h>
#include <zlib.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>

namespace
{

/**
 * Maps the channel counts supported by imogrify to PNG color types. Ignores palette.
 * See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR.
 * @param channels Channel count.
 * @return Color type.
 */
constexpr std::uint8_t to_color_type(const imfy::image::channel_t channels)
{
	using imfy::image::channel_t;
	switch (channels)
	{
		case channel_t::one:
			return SPNG_COLOR_TYPE_GRAYSCALE;
		case channel_t::two:
			return SPNG_COLOR_TYPE_GRAYSCALE_ALPHA;
		case channel_t::three:
			return SPNG_COLOR_TYPE_TRUECOLOR;
		default:
			[[fallthrough]];
		case channel_t::four:
			return SPNG_COLOR_TYPE_TRUECOLOR_ALPHA;
	}
}

/**
 * Maps imogrify compression levels to the levels used by spng.
 * See https://libspng.org/docs/encode
 * @param compression imogrify compression level.
 * @return spng compression level.
 */
constexpr int to_png_compression(const imfy::image::compression_t compression)
{
	using imfy::image::compression_t;
	switch (compression)
	{
		case compression_t::none:
			return Z_NO_COMPRESSION;
		case compression_t::speed:
			return Z_BEST_SPEED;
		default:
			[[fallthrough]];
		case compression_t::standard:
		{
			constexpr int zlib_standard_compression = 6;
			return zlib_standard_compression;
		}
		case compression_t::best:
			return Z_BEST_COMPRESSION;
	}
}

class spng_context final
{
public:
	explicit spng_context(const int flags)
		: _ctx{spng_ctx_new(flags)}
	{
	}

	spng_context(const spng_context&) = delete;
	spng_context(spng_context&&) noexcept = delete;
	spng_context& operator=(const spng_context&) = delete;
	spng_context& operator=(spng_context&&) noexcept = delete;

	~spng_context() { spng_ctx_free(_ctx); }

	[[nodiscard]] spng_ctx* get() const { return _ctx; }

private:
	spng_ctx* _ctx;
};
}

namespace imfy
{

std::size_t encode_spng(const image::raw_image& input_image, const image::compression_t compression_level)
{
	const spng_context context{SPNG_CTX_ENCODER};
	spng_set_option(context.get(), SPNG_ENCODE_TO_BUFFER, 1);
	spng_set_option(context.get(), SPNG_IMG_COMPRESSION_LEVEL, to_png_compression(compression_level));

	spng_ihdr ihdr{};
	ihdr.width = input_image.size().width;
	ihdr.height = input_image.size().height;
	ihdr.color_type = to_color_type(input_image.channels());
	ihdr.bit_depth = static_cast<std::uint8_t>(input_image.bit_depth());
	spng_set_ihdr(context.get(), &ihdr);
	if (const int ret = spng_encode_image(
					context.get(), input_image.data().data(), input_image.data().size(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE
			);
			ret != 0) [[unlikely]]
	{
		std::abort();
	}
	std::size_t buffer_size{};
	int ret{};
	void* IMFY_RESTRICT buffer_data = spng_get_png_buffer(context.get(), &buffer_size, &ret);
	if (ret != 0 || buffer_data == nullptr) [[unlikely]]
	{
		std::abort();
	}

	// NOLINTNEXTLINE(hicpp-no-malloc)
	std::free(buffer_data);

	return buffer_size;
}

}
