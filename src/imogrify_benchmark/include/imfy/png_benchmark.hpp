/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark.hpp>
#include <imfy/markdown.hpp>
#include <imfy/png_encoder.hpp>
#include <imfy/png_format.hpp>
#include <imfy/raw_image.hpp>

#include <cstdint>
#include <string_view>

#include <nanobench.h>

using imfy::png::color_type;

namespace imfy
{

namespace detail
{
std::uint8_t channels_per_color_type(imfy::png::color_type color_type);
raw_image get_initialized_image(std::uint8_t channels, std::uint8_t bit_depth, image_size img_size);

} // namespace detail

void benchmark_png_encoding(
		ankerl::nanobench::Bench& bench, imfy::markdown& mark, imfy::png::color_type color_type, std::uint8_t bit_depth,
		imfy::image_size img_size, std::uint8_t compression_level
);

} // namespace imfy