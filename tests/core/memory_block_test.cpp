/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/memory_block.hpp"

#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <algorithm>
#include <array>
#include <cstdint>
#include <cstring>
#include <memory>

#include <doctest.h>

namespace
{
struct a_simple_struct
{
	std::int64_t first_value;
	std::int8_t second_value;
};

struct a_weird_struct final : public a_simple_struct
{
	std::int8_t third_value;
};

} // namespace

using imfy::memory_block;

TEST_CASE("Types that can be used with memory blocks.")
{
	static_assert(imfy::trivial_standard_layout<std::uint8_t>);
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
	static_assert(imfy::trivial_standard_layout<std::uint8_t[]>);
	static_assert(imfy::trivial_standard_layout<std::array<std::uint8_t, 4U>>);
	static_assert(imfy::trivial_standard_layout<a_simple_struct>);
	static_assert(!imfy::trivial_standard_layout<a_weird_struct>);
	static_assert(!imfy::trivial_standard_layout<memory_block<std::uint64_t>>);
	static_assert(!imfy::trivial_standard_layout<imfy::vector<std::uint8_t>>);
	static_assert(!imfy::trivial_standard_layout<imfy::string>);
	static_assert(!imfy::trivial_standard_layout<std::unique_ptr<std::uint8_t>>);
}

TEST_CASE("Allocating memory blocks of specific sizes")
{
	for (std::size_t size_param{}; size_param <= 8U; ++size_param)
	{
		const memory_block<std::uint64_t> test_block{size_param};
		CHECK(test_block.size() == size_param);
	}
}

TEST_CASE("Setting values in the memory block.")
{
	memory_block<std::uint8_t> block{257U};
	auto span = block.span();
	std::memset(span.data(), 0, span.size());
	CHECK(std::all_of(span.begin(), span.end(), [](const std::uint8_t data) { return data == 0U; }));
}
