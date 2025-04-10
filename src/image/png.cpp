/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png.hpp"

#include <imfy/aligned_allocation.hpp>
#include <imfy/aligned_span.hpp>
#include <imfy/assert.hpp>
#include <imfy/attributes.hpp>
#include <imfy/image_format.hpp>
#include <imfy/memory_block.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/string.hpp>

#include <fmt/format.h>
#include <png.h>
#include <tl/expected.hpp>
#include <zlib.h>

#include <cstdint>
#include <cstring>
#include <stdexcept>
#include <string_view>

namespace
{

class libpng_exception final : public std::runtime_error
{
public:
	libpng_exception(const imfy::string& message, const bool fatal)
		: std::runtime_error(message)
		, fatal_{fatal}
	{
	}

	bool fatal_;
};

void write_data_to_buffer(
		png_struct* IMFY_RESTRICT png_ptr, std::uint8_t* IMFY_RESTRICT data, const std::size_t write_length
)
{
	IMFY_ASSUME(png_ptr != nullptr);
	auto* IMFY_RESTRICT io_pointer = png_get_io_ptr(png_ptr);
	IMFY_ASSUME(io_pointer != nullptr);
	auto& previous_buffer = *static_cast<imfy::memory_block<std::uint8_t>*>(io_pointer);
	imfy::memory_block<std::uint8_t> current_buffer{previous_buffer.size() + write_length};
	if (previous_buffer.size() > 0U) [[likely]]
	{
		std::memcpy(current_buffer.span().data(), previous_buffer.span().data(), current_buffer.size());
		std::memcpy(current_buffer.span().data() + previous_buffer.size(), data, write_length);
	}
	std::swap(previous_buffer, current_buffer);
}

/**
 * Used by libpng to report fatal errors. libpng expects this function to never return to the caller.
 * @param error_msg Error message emitted by libpng.
 */
[[noreturn]] void fatal_error_function(png_struct* /*png_ptr*/, const char* error_msg)
{
	throw libpng_exception(error_msg, true);
}

/**
 * Warnings sent by libpng should be reported back to the user.
 * @param warning_msg Warning message sent by libpng.
 */
[[noreturn]] void warning_function(png_struct* /*png_ptr*/, const char* warning_msg)
{
	throw libpng_exception(warning_msg, false);
}

void* memory_allocation(png_struct* /*png_ptr*/, const std::size_t size)
{
	return imfy::aligned_allocation_bytes(size);
}

void memory_deallocation(png_struct* /*png_ptr*/, void* pointer)
{
	imfy::aligned_deallocation_bytes(pointer);
}

png_struct_def* create_png_struct() noexcept
{
	auto* result = png_create_write_struct_2(
			PNG_LIBPNG_VER_STRING, nullptr, fatal_error_function, warning_function, nullptr, memory_allocation,
			memory_deallocation
	);
	IMFY_ASSUME(result != nullptr);
	return result;
}

class png_info_raii final
{
public:
	png_info_raii()
		: png_struct_{create_png_struct()}
		, info_struct_{png_create_info_struct(png_struct_)}
	{
		IMFY_ASSUME(info_struct_ != nullptr);
	}

	png_info_raii(const png_info_raii&) = delete;
	png_info_raii(png_info_raii&&) = delete;
	png_info_raii& operator=(const png_info_raii&) = delete;
	png_info_raii& operator=(png_info_raii&&) = delete;
	~png_info_raii() { png_destroy_write_struct(&png_struct_, &info_struct_); }

	[[nodiscard]] png_struct_def* png_struct() const { return png_struct_; }
	[[nodiscard]] png_info_def* info_struct() const { return info_struct_; }

private:
	png_struct_def* png_struct_;
	png_info_def* info_struct_;
};

/**
 * Maps the channel counts supported by imogrify to PNG color types. Ignores palette.
 * See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR.
 * @param channels Channel count.
 * @return Color type.
 */
constexpr int to_color_type(const imfy::image::channel_t channels)
{
	using imfy::image::channel_t;
	switch (channels)
	{
		case channel_t::one:
			return PNG_COLOR_TYPE_GRAY;
		case channel_t::two:
			return PNG_COLOR_TYPE_GA;
		case channel_t::three:
			return PNG_COLOR_TYPE_RGB;
		default:
			[[fallthrough]];
		case channel_t::four:
			return PNG_COLOR_TYPE_RGBA;
	}
}

/**
 * Maps imogrify compression levels to the levels used by libpng.
 * See https://www.zlib.net/manual.html
 * @param compression imogrify compression level.
 * @return zlib compression level.
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

tl::expected<imfy::memory_block<std::uint8_t>, imfy::string> do_encode(
		png_struct_def* png_struct, png_info_def* info_struct, const imfy::image::raw_image& image,
		const imfy::image::compression_t compression_level
)
{
	// Errors and RAII are handled in the parent function.
	using namespace imfy;
	png_set_compression_level(png_struct, to_png_compression(compression_level));

	const auto [width, height] = image.size();
	png_set_IHDR(
			png_struct, info_struct, width, height, static_cast<int>(image.bit_depth()), to_color_type(image.channels()),
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);

	// The memory buffer is pre-allocated with an estimated size to reduce repeated resize/copy operations.
	memory_block<std::uint8_t> buffer{};
	png_set_write_fn(png_struct, &buffer, write_data_to_buffer, nullptr);

	png_write_info(png_struct, info_struct);

	const std::uint8_t* IMFY_RESTRICT row_pointer = image.data().data();
	constexpr std::size_t bits_in_byte = 8U;
	const auto byte_depth = static_cast<std::size_t>(image.bit_depth()) / bits_in_byte;
	const auto channels = static_cast<std::uint8_t>(image.channels());

	for (std::size_t row_index = 0U; row_index < height; ++row_index)
	{
		png_write_row(png_struct, row_pointer);
		row_pointer += static_cast<std::size_t>(width) * byte_depth * channels;
	}

	png_write_end(png_struct, info_struct);

	return buffer;
}

}

namespace imfy::png
{

tl::expected<memory_block<std::uint8_t>, string> encode(
		const image::raw_image& input_image, const image::compression_t compression_level
)
{
	const png_info_raii png_info{};
	try
	{
		return do_encode(png_info.png_struct(), png_info.info_struct(), input_image, compression_level);
	}
	catch (const libpng_exception& exception)
	{
		constexpr std::string_view fatal_error = "fatal error";
		constexpr std::string_view error = "error";
		const auto error_description = exception.fatal_ ? fatal_error : error;
		return tl::unexpected{fmt::format("Png encoding {:s}: {:s}", error_description, exception.what())};
	}
}

}
