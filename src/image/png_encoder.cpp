/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_encoder.hpp"

#include <imfy/aligned_allocation.hpp>
#include <imfy/aligned_span.hpp>
#include <imfy/attributes.hpp>
#include <imfy/png_format.hpp>

#include "imfy/image_size.hpp"

#if IMOGRIFY_USE_FMT_BASE_HEADER
#include <fmt/base.h>
#else
// Older versions of fmt lack the fmt/base.h header.
#include <fmt/ostream.h>
#endif // #if IMOGRIFY_USE_FMT_BASE_HEADER

#include <png.h>
#include <tl/expected.hpp>

#include <cstdint>
#include <cstring>
#include <exception>
#include <string_view>

namespace
{

void write_data_to_buffer(png_struct* png_ptr, std::uint8_t* IMFY_RESTRICT data, std::size_t write_length)
{
	auto& output_buffer = *static_cast<imfy::png::encoded_png*>(png_get_io_ptr(png_ptr));
	const auto current_index = output_buffer.size;
	const auto new_size = current_index + write_length;
	if (output_buffer.memory.size() < new_size)
	{
		output_buffer.memory.enlarge(new_size);
	}

	std::memcpy(output_buffer.memory.span().data() + current_index, data, write_length);
	output_buffer.size = new_size;
}

/**
 * Used by libpng to report fatal errors. libpng expects this function to never return to the caller.
 * @param png_ptr Libpng control structure.
 * @param error_msg Error message emitted by libpng.
 */
[[noreturn]] void libpng_fatal_error(png_struct* /*png_ptr*/, const char* error_msg)
{
	fmt::print("Fatal libpng error: {:s}\n", error_msg);
	std::terminate();
}

/**
 * Warnings sent by libpng should be reported back to the user.
 * @param png_ptr Libpng control structure.
 * @param warning_msg Warning message sent by libpng.
 */
void libpng_capture_warning(png_struct* png_ptr, const char* warning_msg)
{
	const char** error_ptr = static_cast<const char**>(png_get_error_ptr(png_ptr));
	*error_ptr = warning_msg;
}

void* libpng_malloc(png_struct* /*png_ptr*/, std::size_t size)
{
	return imfy::aligned_allocation_bytes(size);
}

void libpng_free(png_struct* /*png_ptr*/, void* pointer)
{
	imfy::aligned_deallocation_bytes(pointer);
}

class png_info_raii final
{
public:
	explicit png_info_raii(const char** error)
		: struct_ptr_{png_create_write_struct_2(
					PNG_LIBPNG_VER_STRING,
					error, // NOLINT
					libpng_fatal_error, libpng_capture_warning, nullptr, libpng_malloc, libpng_free
			)}
		, info_ptr_{struct_ptr_ != nullptr ? png_create_info_struct(struct_ptr_) : nullptr}
	{
	}
	png_info_raii(const png_info_raii&) = delete;
	png_info_raii(png_info_raii&&) = delete;
	png_info_raii& operator=(const png_info_raii&) = delete;
	png_info_raii& operator=(png_info_raii&&) = delete;
	~png_info_raii() { png_destroy_write_struct(&struct_ptr_, &info_ptr_); }

	png_struct_def* get_struct() { return struct_ptr_; }
	png_info_def* get_info() { return info_ptr_; }

private:
	png_struct_def* struct_ptr_;
	png_info_def* info_ptr_;
};

using imfy::png::color_type;

std::uint8_t channels_of_color_type(color_type color)
{
	switch (color)
	{
		case color_type::palette:
		case color_type::gray:
			return 1U;
		case color_type::ga:
			return 2U;
		case color_type::rgb:
			return 3U;
		case color_type::rgba:
			return 4U;
		[[unlikely]] default:
			return 0U;
	}
}

} // namespace

namespace imfy::png
{

tl::expected<encoded_png, std::string_view> encode(
		const imfy::png::color_type color, const std::uint8_t bit_depth, const image_size img_size,
		aligned_span<const std::uint8_t> input_image, const std::uint8_t compression_level
)
{
	const char* warning_message = nullptr;
	png_info_raii png_info{&warning_message};
	auto* png_ptr = png_info.get_struct();
	auto* info_ptr = png_info.get_info();
	if (info_ptr == nullptr) [[unlikely]]
	{
		return tl::unexpected("Fatal error during PNG encoding initialization.");
	}

	png_set_compression_level(png_ptr, compression_level);

	png_set_IHDR(
			png_ptr, info_ptr, img_size.width, img_size.height, bit_depth, static_cast<int>(color), PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);

	// The memory buffer is pre-allocated with an estimated size to avoid repeated resize/copy operations.
	encoded_png buffer(input_image.size_bytes());
	png_set_write_fn(png_ptr, &buffer, write_data_to_buffer, nullptr);

	png_write_info(png_ptr, info_ptr);
	// Write PNG file row by row to avoid arrays of row pointers and const casting.
	const std::uint8_t* IMFY_RESTRICT row_pointer = input_image.data();
	constexpr std::uint8_t bits_in_byte = 8U;
	const std::uint8_t byte_depth = bit_depth / bits_in_byte;
	const std::uint8_t channels = channels_of_color_type(color);

	for (std::size_t row_index = 0U; row_index < img_size.height; ++row_index)
	{
		if (warning_message != nullptr) [[unlikely]]
		{
			return tl::unexpected(std::string_view{warning_message});
		}

		png_write_row(png_ptr, row_pointer);
		row_pointer += static_cast<std::size_t>(img_size.width) * byte_depth * channels;
	}
	// Finish writing the image.
	png_write_end(png_ptr, info_ptr);
	return buffer;
}

} // namespace imfy::png