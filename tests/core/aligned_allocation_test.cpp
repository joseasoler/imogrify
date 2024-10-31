/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/aligned_allocation.hpp"

#include <imfy/build.hpp>

#include <hwy/aligned_allocator.h>

#include <cstddef>

#include <doctest/doctest.h>

namespace
{
consteval imfy::build::dependency_t highway_dependency()
{
	for (const auto dependency : imfy::build::dependencies)
	{
		if (dependency.name == "Highway")
		{
			return dependency;
		}
	}
	return {};
}

// HWY_ALIGNMENT became 120 in Highway 1.1.0. HWY_MAJOR changed headers in 1.2.0.
constexpr imfy::build::dependency_t highway_dep = highway_dependency();

} // namespace

TEST_CASE("Match memory alignment size used in Google Highway and imogrify.")
{
	if constexpr (highway_dep.version.major >= 1U && highway_dep.version.minor >= 1U)
	{
		CHECK(imfy::memory_alignment_size == static_cast<std::size_t>(HWY_ALIGNMENT));
	}
}

TEST_CASE("Alignment of allocated memory")
{
	if constexpr (highway_dep.version.major >= 1U && highway_dep.version.minor >= 1U)
	{
		for (std::size_t block_size = 8U; block_size < 128U; block_size += 8U)
		{
			void* data = imfy::aligned_allocation_bytes(block_size);
			const auto intptr = reinterpret_cast<std::uintptr_t>(data); // NOLINT
			CHECK((intptr % imfy::memory_alignment_size) == 0U);
			imfy::aligned_deallocation(data);
		}
	}
}