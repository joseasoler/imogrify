/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/image_format.hpp>

namespace imfy
{
namespace image
{
class raw_image;
}

/**
 * Encode an image as PNG using spng and return its size. Errors are not handled.
 * @param input_image Image to encode.
 * @param compression_level Level of compression to use for encoding.
 * @return Size of the sequence of encoded bytes or an error description.
 */
std::size_t encode_spng(const image::raw_image& input_image, image::compression_t compression_level);

}
