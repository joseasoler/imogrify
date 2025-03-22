/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>
#include <imfy/image_size.hpp>
#include <imfy/png_format.hpp>

#include <cstddef>
#include <cstdint>

namespace imfy
{

std::size_t encode_spng(
		png::color_t color, image::bit_depth_t bit_depth, image::image_size img_size,
		aligned_span<const std::uint8_t> input_image, image::compression_t compression
);

}
