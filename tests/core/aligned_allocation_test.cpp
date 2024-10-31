/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/aligned_allocation.hpp"

#include <hwy/aligned_allocator.h>

#include <cstddef>

#include <doctest/doctest.h>

TEST_CASE("Match memory alignment size used in Google Highway and imogrify.")
{
	static_assert(imfy::memory_alignment_size == static_cast<std::size_t>(HWY_ALIGNMENT));
}

TEST_CASE("Alignment of allocated memory")
{
	void* data = imfy::aligned_allocation(64U);
	CHECK(hwy::IsAligned(data, imfy::memory_alignment_size));
	imfy::aligned_deallocation(data);
}