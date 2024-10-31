/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/raw_image.hpp"

#include <imfy/image_size.hpp>

#include <cstddef>
#include <cstdint>

#include <doctest/doctest.h>

using imfy::image_size;
using imfy::raw_image;

namespace
{

[[nodiscard]] bool parameter_checks(
		std::uint8_t channels, std::uint8_t bit_depth, image_size img_size, const raw_image& test_image
)
{
	return test_image.channels() == channels && test_image.bit_depth() == bit_depth && test_image.size() == img_size;
}

void raw_image_checks(std::uint8_t channels, std::uint8_t bit_depth, image_size img_size)
{
	const raw_image test_image(channels, bit_depth, img_size);
	CHECK(parameter_checks(channels, bit_depth, img_size, test_image));
	const auto area = static_cast<std::size_t>(img_size.width) * img_size.height;
	const auto byte_depth = bit_depth / 8U;
	const auto real_byte_size = test_image.data().size();
	const auto expected_byte_size = area * channels * byte_depth;
	CHECK(real_byte_size == expected_byte_size);
}

} // Anonymous namespace

TEST_CASE("Raw image")
{
	raw_image_checks(4U, 8U, {24U, 38U});
	raw_image_checks(2U, 16U, {1024U, 2048U});
}
