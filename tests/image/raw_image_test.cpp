/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/raw_image.hpp"

#include <imfy/image_size.hpp>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <type_traits>

#include <doctest/doctest.h>

using imfy::image::image_size;
using imfy::image::raw_image;

namespace
{

constexpr image_size default_size{32U, 16U};

template <std::uint8_t Channels, std::uint8_t BitSize>
void raw_image_checks()
{
	using raw_image_t = raw_image<Channels, BitSize>;
	const raw_image_t test_image(default_size);
	CHECK(test_image.width() == default_size.width);
	CHECK(test_image.height() == default_size.height);
	const auto area = static_cast<std::size_t>(default_size.width) * default_size.height;
	CHECK(test_image.data().size() == area * Channels);
	CHECK(test_image.raw_data().size() == area * Channels * sizeof(typename raw_image_t::value_type));
}

template <std::uint8_t Channels, std::uint8_t BitSize>
bool consecutive_values_are_different()
{
	const raw_image<Channels, BitSize> image(default_size, imfy::image::initialization::modulo);
	const auto data = image.data();
	bool result = true;
	for (std::size_t index = 0U; index < (data.size() - Channels); ++index)
	{
		result = data[index] != data[index + Channels];
		if (!result)
		{
			break;
		}
	}
	return result;
}
} // Anonymous namespace

TEST_CASE("Raw image type checks")
{
	static_assert(std::is_same_v<raw_image<1U, 8U>::value_type, std::uint8_t>);
	static_assert(std::is_same_v<raw_image<3U, 8U>::value_type, std::uint8_t>);
	static_assert(std::is_same_v<raw_image<1U, 16U>::value_type, std::uint16_t>);
	static_assert(std::is_same_v<raw_image<2U, 16U>::value_type, std::uint16_t>);
}

TEST_CASE("Uninitialized raw image")
{
	raw_image_checks<4U, 8U>();
	raw_image_checks<2U, 16U>();
}

TEST_CASE("Zeroed raw image")
{
	const raw_image<4U, 16U> image(default_size, imfy::image::initialization::zero);
	const auto data = image.data();
	CHECK(std::all_of(data.begin(), data.end(), [](std::uint16_t value) -> bool { return value == 0U; }));
}

TEST_CASE("Modulo raw image")
{
	CHECK(consecutive_values_are_different<1U, 8U>());
	CHECK(consecutive_values_are_different<2U, 16U>());
	CHECK(consecutive_values_are_different<3U, 8U>());
	CHECK(consecutive_values_are_different<4U, 16U>());
}