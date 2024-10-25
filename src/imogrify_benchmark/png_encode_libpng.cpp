/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_encode_libpng.hpp"

#include <imfy/png_format.hpp>
#include <imfy/vector.hpp>

#include <png.h>

#include <cstdint>
#include <cstdlib>
#include <cstring>
#include <span>

namespace
{
using data_buffer = imfy::vector<std::uint8_t>;

void write_data_to_buffer(png_struct* png_ptr, std::uint8_t* data, std::size_t write_length)
{
	auto& output_buffer = *static_cast<data_buffer*>(png_get_io_ptr(png_ptr));
	const auto current_size = output_buffer.size();
	const auto new_size = current_size + write_length;
	if (output_buffer.size() < new_size)
	{
		output_buffer.resize(new_size);
	}

	std::memcpy(&output_buffer[current_size], data, write_length);
}

[[noreturn]] void libpng_abort_on_error(png_struct* /*png_ptr*/, const char* /*error_msg*/)
{
	std::abort();
}

void* libpng_malloc(png_struct* /*png_ptr*/, std::size_t size)
{
	// NOLINTNEXTLINE(cppcoreguidelines-no-malloc, hicpp-no-malloc)
	void* raw_memory = std::malloc(size);
	if (raw_memory == nullptr) [[unlikely]]
	{
		std::abort();
	}
	return raw_memory;
}

void libpng_free(png_struct* /*png_ptr*/, void* raw_memory)
{
	// NOLINTNEXTLINE(cppcoreguidelines-no-malloc, hicpp-no-malloc)
	std::free(raw_memory);
}

} // namespace

namespace imfy
{

/*
std::size_t encode_libpng(
		const std::uint32_t width, const std::uint32_t height, const std::span<const std::uint8_t> input_image,
		const std::uint8_t color_type, const std::uint8_t bit_depth, const std::uint8_t compression_level
)
 */
std::size_t encode_libpng(
		imfy::png::color_type color, std::uint8_t bit_depth, std::uint32_t width, std::uint32_t height,
		std::span<const std::uint8_t> input_image, std::uint8_t compression_level
)
{
	png_struct_def* png_ptr = png_create_write_struct_2(
			PNG_LIBPNG_VER_STRING, nullptr, libpng_abort_on_error, libpng_abort_on_error, nullptr, libpng_malloc, libpng_free
	);
	if (png_ptr == nullptr) [[unlikely]]
	{
		std::abort();
	}

	png_info_def* info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == nullptr) [[unlikely]]
	{
		png_destroy_write_struct(&png_ptr, nullptr);
		std::abort();
	}

	png_set_compression_level(png_ptr, compression_level);

	png_set_IHDR(
			png_ptr, info_ptr, width, height, bit_depth, static_cast<int>(color), PNG_INTERLACE_NONE,
			PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT
	);

	// Write data to a memory buffer.
	data_buffer buffer{};
	png_set_write_fn(png_ptr, &buffer, write_data_to_buffer, nullptr);

	png_write_info(png_ptr, info_ptr);
	// Write PNG file row by row to avoid arrays of row pointers and const casting.
	const std::uint8_t* row_pointer = input_image.data();
	constexpr std::uint8_t bits_in_byte = 8U;
	const std::uint8_t byte_depth = bit_depth / bits_in_byte;
	std::uint8_t channels{};

	using imfy::png::color_type;
	switch (color)
	{
		case color_type::palette:
		case color_type::gray:
			channels = 1U;
			break;
		case color_type::ga:
			channels = 2U;
			break;
		case color_type::rgb:
			channels = 3U;
			break;
		case color_type::rgba:
			channels = 4U;
			break;
		[[unlikely]] default:
			std::abort();
	}

	for (std::size_t row_index = 0U; row_index < height; ++row_index)
	{
		png_write_row(png_ptr, row_pointer);
		// NOLINTNEXTLINE(cppcoreguidelines-pro-bounds-pointer-arithmetic)
		row_pointer += static_cast<std::size_t>(width) * byte_depth * channels;
	}
	// Finish writing the image and clean up memory.
	png_write_end(png_ptr, info_ptr);
	png_destroy_write_struct(&png_ptr, &info_ptr);

	// ToDo
	/*
	std::ofstream dmp{"libpng.png", std::ios::out | std::ios::binary};
	dmp.write(reinterpret_cast<const char*>(buffer.data()), static_cast<std::ptrdiff_t>(buffer.size())); // NOLINT
	*/

	return buffer.size();
}

} // namespace imfy