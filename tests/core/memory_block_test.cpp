/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/memory_block.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>

#include <doctest/doctest.h>

using imfy::memory_block;

TEST_CASE("Allocating memory blocks of specific sizes")
{
	constexpr std::size_t block_size_max = 8U;
	for (std::size_t size_param{1U}; size_param <= block_size_max; ++size_param)
	{
		const memory_block<std::uint64_t> test_block{size_param};
		CHECK(test_block.size() == size_param);
	}
}

TEST_CASE("Setting values in the memory block.")
{
	constexpr std::size_t memory_block_size = 257U;
	memory_block<std::uint8_t> block{memory_block_size};
	const auto span = block.span();
	std::memset(span.data(), 0, span.size());
	CHECK(std::all_of(span.data(), span.data() + span.size(), [](const std::uint8_t data) { return data == 0U; }));
}
