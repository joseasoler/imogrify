/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/raw_image.hpp"

#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>

#include <cstddef>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>

using namespace imfy::image;

namespace
{

[[nodiscard]] bool parameter_checks(
		const channel_t channels, const bit_depth_t bit_depth, image_size img_size, const raw_image& test_image
)
{
	return test_image.channels() == channels && test_image.bit_depth() == bit_depth && test_image.size() == img_size;
}

void raw_image_checks(const channel_t channels, const bit_depth_t bit_depth, image_size img_size)
{
	const raw_image test_image(channels, bit_depth, img_size);
	CHECK(parameter_checks(channels, bit_depth, img_size, test_image));
	const auto area = static_cast<std::size_t>(img_size.width) * img_size.height;
	const auto byte_depth = byte_size(bit_depth);
	const auto real_byte_size = test_image.data().size();
	const auto expected_byte_size = area * static_cast<std::size_t>(channels) * byte_depth;
	CHECK(real_byte_size == expected_byte_size);
}

}

TEST_CASE("Raw image")
{
	constexpr uint16_t small_width = 24U;
	constexpr uint16_t small_height = 38U;
	raw_image_checks(channel_t::four, bit_depth_t::eight, {.width = small_width, .height = small_height});
	constexpr uint16_t large_width = 1024U;
	constexpr uint16_t large_height = 2048U;
	raw_image_checks(channel_t::two, bit_depth_t::sixteen, {.width = large_width, .height = large_height});
}
