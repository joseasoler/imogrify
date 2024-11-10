/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>
#include <imfy/png_format.hpp>

#include <tl/expected.hpp>

#include <string_view>

namespace imfy::png
{

// Since the encoder may allocate more memory than strictly necessary, this structure includes the actual encoded size.
struct encoded_png final
{
	std::size_t size{};
	imfy::memory_block<std::uint8_t> memory;

	explicit encoded_png(std::size_t buffer_size)
		: memory(buffer_size)
	{
	}
	encoded_png(const encoded_png&) = delete;
	encoded_png(encoded_png&&) noexcept = default;
	encoded_png& operator=(const encoded_png&) = delete;
	encoded_png& operator=(encoded_png&&) noexcept = default;
	~encoded_png() = default;
};

tl::expected<encoded_png, std::string_view> encode(
		color_t color, image::bit_depth_t bit_depth, image::image_size img_size,
		aligned_span<const std::uint8_t> input_image, image::compression_t compression_level
);

} // namespace imfy::png
