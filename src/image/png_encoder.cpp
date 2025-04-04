/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_encoder.hpp"

#include <imfy/aligned_allocation.hpp>
#include <imfy/aligned_span.hpp>
#include <imfy/assert.hpp>
#include <imfy/attributes.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/png_format.hpp>
#include <imfy/vector.hpp>

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

void write_data_to_buffer(
		png_struct* IMFY_RESTRICT png_ptr, std::uint8_t* IMFY_RESTRICT data, const std::size_t write_length
)
{
	IMFY_ASSUME(png_ptr != nullptr);
	auto* IMFY_RESTRICT io_pointer = png_get_io_ptr(png_ptr);
	IMFY_ASSUME(io_pointer != nullptr);
	auto& output_buffer = *static_cast<imfy::vector<std::uint8_t>*>(io_pointer);
	const auto current_index = output_buffer.size();
	const auto new_size = current_index + write_length;
	if (output_buffer.size() < new_size)
	{
		output_buffer.resize(new_size);
	}

	std::memcpy(output_buffer.data() + current_index, data, write_length);
}

/**
 * Used by libpng to report fatal errors. libpng expects this function to never return to the caller.
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
void libpng_capture_warning(png_struct* IMFY_RESTRICT png_ptr, const char* warning_msg)
{
	auto* const error_ptr = static_cast<const char**>(png_get_error_ptr(png_ptr));
	IMFY_ASSUME(error_ptr != nullptr);
	*error_ptr = warning_msg;
}

void* libpng_malloc(png_struct* /*png_ptr*/, const std::size_t size)
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
					// NOLINTNEXTLINE(bugprone-multi-level-implicit-pointer-conversion)
					static_cast<void*>(error), libpng_fatal_error, libpng_capture_warning, nullptr, libpng_malloc, libpng_free
			)}
		, info_ptr_{png_create_info_struct(struct_ptr_)}
	{
		IMFY_ASSUME(struct_ptr_ != nullptr);
		IMFY_ASSUME(info_ptr_ != nullptr);
	}

	png_info_raii(const png_info_raii&) = delete;
	png_info_raii(png_info_raii&&) = delete;
	png_info_raii& operator=(const png_info_raii&) = delete;
	png_info_raii& operator=(png_info_raii&&) = delete;
	~png_info_raii() { png_destroy_write_struct(&struct_ptr_, &info_ptr_); }

	[[nodiscard]] png_struct_def* get_struct() const { return struct_ptr_; }
	[[nodiscard]] png_info_def* get_info() const { return info_ptr_; }

private:
	png_struct_def* struct_ptr_;
	png_info_def* info_ptr_;
};

using imfy::png::color_t;

std::uint8_t channels_of_color_type(const color_t color)
{
	switch (color)
	{
		case color_t::palette:
		case color_t::gray:
			return 1U;
		case color_t::ga:
			return 2U;
		case color_t::rgb:
			return 3U;
		case color_t::rgba:
			return 4U;
		[[unlikely]] default:
			return 0U;
	}
}

}

namespace imfy::png
{

tl::expected<vector<std::uint8_t>, std::string_view> encode(
		const color_t color, const image::bit_depth_t bit_depth, const image::image_size img_size,
		aligned_span<const std::uint8_t> input_image, const image::compression_t compression
)
{
	const char* warning_message = nullptr;
	const png_info_raii png_info{&warning_message};
	auto* png_ptr = png_info.get_struct();
	auto* info_ptr = png_info.get_info();
	if (info_ptr == nullptr) [[unlikely]]
	{
		return tl::unexpected("Fatal error during PNG encoding initialization.");
	}

	png_set_compression_level(png_ptr, png::to_png_compression(compression));

	png_set_IHDR(
			png_ptr, info_ptr, img_size.width, img_size.height, static_cast<int>(bit_depth), static_cast<int>(color),
			PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);

	// The memory buffer is pre-allocated with an estimated size to reduce repeated resize/copy operations.
	vector<std::uint8_t> buffer(input_image.size_bytes());
	png_set_write_fn(png_ptr, &buffer, write_data_to_buffer, nullptr);

	png_write_info(png_ptr, info_ptr);
	// Write PNG file row by row to avoid arrays of row pointers and const casting.
	const std::uint8_t* IMFY_RESTRICT row_pointer = input_image.data();
	constexpr std::uint8_t bits_in_byte = 8U;
	const std::uint8_t byte_depth = static_cast<std::uint8_t>(bit_depth) / bits_in_byte;
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

	png_write_end(png_ptr, info_ptr);
	return buffer;
}

}
