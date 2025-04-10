/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/memory_block.hpp"

#include <algorithm>
#include <cstdint>
#include <cstring>

#include <catch2/catch_test_macros.hpp>

using imfy::memory_block;

TEST_CASE("Construction of empty blocks.")
{
	const memory_block<std::uint64_t> test_block{};
	CHECK(test_block.size() == 0U);
	CHECK(test_block.span().data() == nullptr);
	CHECK(test_block.span().size_bytes() == 0U);
}

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
	constexpr std::uint8_t value = 7U;
	std::memset(span.data(), value, span.size());
	CHECK(std::all_of(span.data(), span.data() + span.size(), [](const std::uint8_t data) { return data == value; }));
}

TEST_CASE("Swapping memory blocks")
{
	constexpr std::size_t block_a_size = 8U;
	constexpr std::uint8_t block_a_value = 123U;
	memory_block<std::uint8_t> block_a{block_a_size};
	std::memset(block_a.span().data(), block_a_value, block_a.span().size());
	CHECK(block_a.span()[0U] == block_a_value);

	constexpr std::size_t block_b_size = 12U;
	constexpr std::uint8_t block_b_value = 32U;
	memory_block<std::uint8_t> block_b{block_b_size};
	std::memset(block_b.span().data(), block_b_value, block_b.span().size());
	CHECK(block_b.span()[0U] == block_b_value);

	std::swap(block_a, block_b);
	CHECK(block_a.size() == block_b_size);
	CHECK(block_a.span()[0] == block_b_value);

	CHECK(block_b.size() == block_a_size);
	CHECK(block_b.span()[0] == block_a_value);
}
