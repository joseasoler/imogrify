/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/png_format.hpp"

#include <cstdint>

namespace imfy::png
{

color_type color_type_from_channels(const std::uint8_t channels)
{
	switch (channels)
	{
		case 1U:
			return color_type::gray;
		case 2U:
			return color_type::ga;
		case 3U:
			return color_type::rgb;
		default:
		case 4U:
			return color_type::rgba;
	}
}

} // namespace imfy::png