/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>

namespace imfy
{

struct image_size final
{
	std::uint16_t width;
	std::uint16_t height;
	bool operator==(const image_size& rhs) const noexcept { return width == rhs.width && height == rhs.height; }
	bool operator!=(const image_size& rhs) const noexcept { return width != rhs.width || height != rhs.height; }
};

} // namespace imfy