/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/image_size.hpp"

#include <imfy/concepts.hpp>

#include <cstdint>

#include <catch2/catch_test_macros.hpp>

using imfy::image::image_size;

TEST_CASE("Basic image_size checks")
{
	static_assert(imfy::pod_type<image_size>);
	static_assert(sizeof(image_size) == sizeof(std::uint32_t));
	constexpr std::uint16_t width = 12U;
	constexpr std::uint16_t height = 17U;
	constexpr image_size size_test{.width = width, .height = height};
	static_assert(size_test.width == width);
	static_assert(size_test.height == height);
}

TEST_CASE("image_size comparison checks")
{
	constexpr std::uint16_t small_size = 8U;
	constexpr std::uint16_t large_size = 2048U;

	constexpr image_size small_small{.width = small_size, .height = small_size};
	constexpr image_size small_large{.width = small_size, .height = large_size};
	constexpr image_size large_small{.width = large_size, .height = small_size};
	constexpr image_size large_large{.width = large_size, .height = large_size};

	constexpr image_size other_small_small{.width = small_size, .height = small_size};
	static_assert(small_small == other_small_small);
	static_assert(small_small <= other_small_small);
	static_assert(small_small >= other_small_small);
	static_assert(!(small_small != other_small_small));
	static_assert(!(small_small < other_small_small));
	static_assert(!(small_small > other_small_small));

	static_assert(small_small != small_large);
	static_assert(small_small != large_small);
	static_assert(small_small != large_large);

	static_assert(small_small < small_large);
	static_assert(small_small <= small_large);
	static_assert(small_small < large_small);
	static_assert(small_small <= large_small);
	static_assert(small_small < large_large);
	static_assert(small_small <= large_large);

	static_assert(small_large > small_small);
	static_assert(small_large >= small_small);
	static_assert(large_small > small_small);
	static_assert(large_small >= small_small);
	static_assert(large_large > small_small);
	static_assert(large_large >= small_small);

	static_assert(small_large != large_small);
	static_assert(small_large < large_small);
	static_assert(small_large <= large_small);

	static_assert(large_small > small_large);
	static_assert(large_small >= small_large);
}
