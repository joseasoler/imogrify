/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>
#include <imfy/png_format.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace imfy::png
{

tl::expected<vector<std::uint8_t>, std::string_view> encode(
		color_t color, image::bit_depth_t bit_depth, image::image_size img_size,
		aligned_span<const std::uint8_t> input_image, image::compression_t compression_level
);

}
