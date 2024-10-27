/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_size.hpp>
#include <imfy/png_format.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

#include <span>
#include <string_view>

namespace imfy::png
{

tl::expected<imfy::vector<std::uint8_t>, std::string_view> encode(
		imfy::png::color_type color, std::uint8_t bit_depth, image_size img_size, std::span<const std::uint8_t> input_image,
		std::uint8_t compression_level
);

} // namespace imfy::png
