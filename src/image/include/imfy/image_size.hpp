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

	constexpr bool operator==(const image_size& rhs) const noexcept = default;
	constexpr bool operator!=(const image_size& rhs) const noexcept = default;
};

/**
 * image_size instances are sorted by their total size, then by width, and then by height.
 * Size sorting is intended for benchmarks.
 * @param lhs First instance to compare.
 * @param rhs Second instance to compare.
 * @return Ordering of the two image sizes.
 */
constexpr std::strong_ordering operator<=>(const image_size& lhs, const image_size& rhs) noexcept
{
	const std::uint32_t lhs_size = lhs.width * lhs.height;
	const std::uint32_t rhs_size = rhs.width * rhs.height;

	if (const auto size_comparison = lhs_size <=> rhs_size; size_comparison != std::strong_ordering::equal)
	{
		return size_comparison;
	}

	if (const auto width_comparison = lhs.width <=> rhs.width; width_comparison != std::strong_ordering::equal)
	{
		return width_comparison;
	}

	return lhs.height <=> rhs.height;
}

}
