/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_format.hpp>
#include <imfy/memory_block.hpp>
#include <imfy/string.hpp>

#include <tl/expected.hpp>

#include <cstdint>

namespace imfy::image
{
class raw_image;
}

namespace imfy::png
{

/**
 * Encode an image as PNG. PNG color type is deduced from channel count.
 * @param input_image Image to encode.
 * @param compression_level Level of compression to use for encoding.
 * @return Sequence of encoded bytes or an error description.
 */
tl::expected<memory_block<std::uint8_t>, string> encode(
		const image::raw_image& input_image, image::compression_t compression_level
);

}
