/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>

namespace imfy::image
{

enum class channel_t : std::uint8_t
{
	one = 1U,
	two = 2U,
	three = 3U,
	four = 4U,
};

enum class bit_depth_t : std::uint8_t
{
	eight = 8U,
	sixteen = 16U,
};

enum class compression_t : std::uint8_t
{
	none,
	speed,
	standard,
	best,
};

}
