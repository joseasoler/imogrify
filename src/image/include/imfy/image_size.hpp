/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <compare>
#include <cstdint>

namespace imfy
{

struct image_size final
{
	std::uint16_t width;
	std::uint16_t height;

	/**
	 * image_size instances are sorted by their total size, then by width, and then by height.
	 * Sorting is required by benchmarks.
	 * @param rhs image_size instance to compare to.
	 * @return Ordering of the two image sizes.
	 */
	constexpr std::strong_ordering operator<=>(const image_size& rhs) const noexcept
	{
		const std::uint32_t lhs_size = width * height;
		const std::uint32_t rhs_size = rhs.width * rhs.height;
		if (lhs_size == rhs_size)
		{
			if (width == rhs.width)
			{
				if (height == rhs.height)
				{
					return std::strong_ordering::equal;
				}
				return height < rhs.height ? std::strong_ordering::less : std::strong_ordering::greater;
			}
			return width < rhs.width ? std::strong_ordering::less : std::strong_ordering::greater;
		}

		return lhs_size < rhs_size ? std::strong_ordering::less : std::strong_ordering::greater;
	}

	constexpr bool operator==(const image_size& rhs) const noexcept { return width == rhs.width && height == rhs.height; }
	constexpr bool operator!=(const image_size& rhs) const noexcept { return width != rhs.width || height != rhs.height; }
};

} // namespace imfy