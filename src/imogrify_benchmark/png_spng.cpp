/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_spng.hpp"

#include <imfy/png_format.hpp>

#include <spng.h>

#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>

using imfy::png::color_type;

namespace
{
static_assert(static_cast<int>(color_type::gray) == SPNG_COLOR_TYPE_GRAYSCALE);
static_assert(static_cast<int>(color_type::ga) == SPNG_COLOR_TYPE_GRAYSCALE_ALPHA);
static_assert(static_cast<int>(color_type::palette) == SPNG_COLOR_TYPE_INDEXED);
static_assert(static_cast<int>(color_type::rgb) == SPNG_COLOR_TYPE_TRUECOLOR);
static_assert(static_cast<int>(color_type::rgba) == SPNG_COLOR_TYPE_TRUECOLOR_ALPHA);

class spng_context final
{
public:
	explicit spng_context(int flags)
		: _ctx{spng_ctx_new(flags)}
	{
	}

	spng_context(const spng_context&) = delete;
	spng_context(spng_context&&) noexcept = delete;
	spng_context& operator=(const spng_context&) = delete;
	spng_context& operator=(spng_context&&) noexcept = delete;

	~spng_context() { spng_ctx_free(_ctx); }

	spng_ctx* get() { return _ctx; }

private:
	spng_ctx* _ctx;
};
} // namespace

namespace imfy
{

std::size_t encode_spng(
		const color_type color, const std::uint8_t bit_depth, const std::uint32_t width, const std::uint32_t height,
		std::span<const std::uint8_t> input_image, const std::uint8_t compression_level
)
{
	spng_context context{SPNG_CTX_ENCODER};
	spng_set_option(context.get(), SPNG_ENCODE_TO_BUFFER, 1);
	spng_set_option(context.get(), SPNG_IMG_COMPRESSION_LEVEL, compression_level);

	spng_ihdr ihdr{};
	ihdr.width = width;
	ihdr.height = height;
	ihdr.color_type = static_cast<std::uint8_t>(color);
	ihdr.bit_depth = bit_depth;
	spng_set_ihdr(context.get(), &ihdr);
	if (const int ret =
					spng_encode_image(context.get(), input_image.data(), input_image.size(), SPNG_FMT_PNG, SPNG_ENCODE_FINALIZE);
			ret != 0) [[unlikely]]
	{
		if (ret == SPNG_EBUFSIZ)
		{
			spng_set_option(context.get(), SPNG_ENCODE_TO_BUFFER, 1);
		}
		std::abort();
	}
	std::size_t buffer_size{};
	int ret{};
	void* buffer_data = spng_get_png_buffer(context.get(), &buffer_size, &ret);
	if (ret != 0 || buffer_data == nullptr) [[unlikely]]
	{
		std::abort();
	}

	// NOLINTNEXTLINE(cppcoreguidelines-no-malloc, hicpp-no-malloc)
	std::free(buffer_data);

	return buffer_size;
}

} // namespace imfy