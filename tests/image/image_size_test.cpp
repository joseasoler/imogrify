/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/image_size.hpp"

#include <cstdint>

#include <doctest/doctest.h>

using imfy::image_size;

TEST_CASE("Basic image_size checks")
{
	static_assert(sizeof(image_size) == 4U);
	constexpr std::uint16_t width = 12U;
	constexpr std::uint16_t height = 17U;
	constexpr image_size size_test{width, height};
	static_assert(size_test.width == width);
	static_assert(size_test.height == 17U);
}