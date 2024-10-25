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

constexpr image_size default_size{18U, 19U};

template <std::uint8_t Channels, std::uint8_t BitSize>
bool test_modulo_raw_image()
{
	const raw_image<Channels, BitSize> image(default_size, imfy::image::initialization::modulo);
	const auto data = image.data();
	bool result = true;
	for (std::size_t index = 0U; result && index < (data.size() - raw_image<Channels, BitSize>::pixel_size); ++index)
	{
		result = data[index] != data[index + raw_image<Channels, BitSize>::pixel_size];
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
	const raw_image<4U, 8U> image_8(default_size);
	CHECK(image_8.width() == default_size.width);
	CHECK(image_8.height() == default_size.height);
	CHECK(
			image_8.data().size() ==
			static_cast<std::size_t>(default_size.width) * default_size.height * raw_image<4U, 8U>::pixel_size
	);

	const raw_image<2U, 8U> image_16(default_size);
	CHECK(image_16.width() == default_size.width);
	CHECK(image_16.height() == default_size.height);
	CHECK(
			image_16.data().size() ==
			static_cast<std::size_t>(default_size.width) * default_size.height * raw_image<2U, 8U>::pixel_size
	);
}

TEST_CASE("Zeroed raw image")
{
	const raw_image<4U, 16U> image(default_size, imfy::image::initialization::zero);
	const auto data = image.data();
	CHECK(std::all_of(data.begin(), data.end(), [](std::uint16_t value) -> bool { return value == 0U; }));
}

TEST_CASE("Modulo raw image")
{
	CHECK(test_modulo_raw_image<1U, 8U>());
	CHECK(test_modulo_raw_image<2U, 16U>());
	CHECK(test_modulo_raw_image<3U, 8U>());
	CHECK(test_modulo_raw_image<4U, 16U>());
}