/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/image_size.hpp"

#include <imfy/concepts.hpp>

#include <cstdint>

#include <doctest/doctest.h>

using imfy::image::image_size;

TEST_CASE("Basic image_size checks")
{
	static_assert(imfy::pod_type<image_size>);
	static_assert(sizeof(image_size) == sizeof(std::uint32_t));
	constexpr std::uint16_t width = 12U;
	constexpr std::uint16_t height = 17U;
	constexpr image_size size_test(width, height);
	static_assert(size_test.width == width);
	static_assert(size_test.height == 17U);
}

TEST_CASE("image_size comparison checks")
{
	constexpr std::uint16_t small_size = 8U;
	constexpr std::uint16_t large_side = 2048U;
	static_assert(image_size(small_size, small_size) == image_size(small_size, small_size));

	static_assert(image_size(small_size, large_side) != image_size(large_side, small_size));

	static_assert(image_size(small_size, small_size) < image_size(large_side, large_side));
	static_assert(image_size(small_size, large_side) < image_size(large_side, small_size));

	static_assert(image_size(small_size, small_size) <= image_size(small_size, small_size));
	static_assert(image_size(small_size, small_size) <= image_size(large_side, small_size));
	static_assert(image_size(small_size, large_side) <= image_size(large_side, small_size));

	static_assert(image_size(large_side, large_side) > image_size(small_size, small_size));
	static_assert(image_size(large_side, small_size) > image_size(small_size, large_side));

	static_assert(image_size(small_size, small_size) >= image_size(small_size, small_size));
	static_assert(image_size(large_side, small_size) >= image_size(small_size, small_size));
	static_assert(image_size(large_side, small_size) >= image_size(small_size, large_side));
}