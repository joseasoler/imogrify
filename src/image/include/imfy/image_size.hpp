/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <compare>
#include <cstdint>

namespace imfy::image
{

struct image_size final
{
	std::uint16_t width;
	std::uint16_t height;

	/**
	 * image_size instances are sorted by their total size, then by width, and then by height.
	 * Size sorting is intended for benchmarks.
	 * @param rhs image_size instance to compare to.
	 * @return Ordering of the two image sizes.
	 */
	constexpr std::strong_ordering operator<=>(const image_size& rhs) const noexcept
	{
		const std::uint32_t lhs_size = width * height;
		const std::uint32_t rhs_size = rhs.width * rhs.height;

		if (const auto size_comparison = lhs_size <=> rhs_size; size_comparison != std::strong_ordering::equal)
		{
			return size_comparison;
		}

		if (const auto width_comparison = width <=> rhs.width; width_comparison != std::strong_ordering::equal)
		{
			return width_comparison;
		}

		return height <=> rhs.height;
	}

	constexpr bool operator==(const image_size& rhs) const noexcept { return width == rhs.width && height == rhs.height; }

	constexpr bool operator!=(const image_size& rhs) const noexcept { return width != rhs.width || height != rhs.height; }
};

}
