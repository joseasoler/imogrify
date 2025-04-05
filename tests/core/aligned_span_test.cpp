/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/aligned_span.hpp"

#include <imfy/aligned_allocation.hpp>

#include <cstddef>
#include <cstdint>

#include <catch2/catch_test_macros.hpp>

using imfy::aligned_span;

TEST_CASE("Type traits checks.")
{
	static_assert(sizeof(aligned_span<unsigned int>) == sizeof(std::size_t) + sizeof(void*));
}

TEST_CASE("Constructor checks.")
{
	const aligned_span<std::uint8_t> empty_span;
	CHECK(empty_span.data() == nullptr);
	CHECK(empty_span.empty());

	constexpr std::uint16_t initial_value{32U};
	constexpr std::size_t allocation_size{64U};
	auto* allocation_input = imfy::aligned_allocation<std::uint32_t>(allocation_size);
	*allocation_input = initial_value;
	const aligned_span<std::uint32_t> array_span(allocation_input, allocation_size);
	CHECK(array_span.data() != nullptr);
	CHECK(array_span.size() == allocation_size);
	CHECK(array_span.size_bytes() == allocation_size * sizeof(std::uint32_t));
	CHECK(*array_span.data() == initial_value);
	imfy::aligned_deallocation<std::uint32_t>(allocation_input);
}

TEST_CASE("as_bytes checks.")
{
	constexpr std::uint16_t initial_value{0xFFU};
	constexpr std::size_t allocation_size{1U};
	auto* allocation_input = imfy::aligned_allocation<std::uint16_t>(allocation_size);
	*allocation_input = initial_value;
	aligned_span span(allocation_input, allocation_size);
	const auto bytes_span = span.as_bytes();
	CHECK(*bytes_span.data() == initial_value);

	auto writable_bytes_span = span.as_writable_bytes();
	constexpr std::uint8_t set_value{0xAU};
	constexpr std::uint16_t expected_value = (set_value << 8U) + set_value;
	writable_bytes_span[0U] = set_value;
	writable_bytes_span[1U] = set_value;
	CHECK(span[0] == expected_value);
	imfy::aligned_deallocation<std::uint16_t>(allocation_input);
}
