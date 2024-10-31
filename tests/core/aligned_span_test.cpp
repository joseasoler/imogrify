/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/aligned_span.hpp"

#include <imfy/aligned_allocation.hpp>

#include <hwy/aligned_allocator.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include <doctest/doctest.h>

using imfy::aligned_span;

TEST_CASE("Type traits checks.")
{
	static_assert(sizeof(aligned_span<unsigned int>) == (sizeof(std::size_t) + sizeof(void*)));
}

TEST_CASE("Constructor checks.")
{
	const aligned_span<std::uint8_t> empty_span;
	CHECK(empty_span.data() == nullptr);
	CHECK(empty_span.empty());

	constexpr std::array<std::uint32_t, 4U> array_input{32U, 8U, 16U, 64U};
	const aligned_span array_span(array_input.data(), array_input.size());
	CHECK(array_span.data() != nullptr);
	CHECK(hwy::IsAligned(array_span.data(), imfy::memory_alignment_size));
	CHECK(array_span.size() == array_input.size());
	CHECK(array_span.size_bytes() == array_input.size() * sizeof(std::uint32_t));
	CHECK(*array_span.data() == array_input[0U]);
}

TEST_CASE("as_bytes checks.")
{
	constexpr std::uint16_t initial_value{0xFFU};
	std::array<std::uint16_t, 2U> array_input{initial_value, 0x00U};
	const imfy::aligned_span span(array_input.data(), array_input.size());
	auto bytes_span = span.as_bytes();
	CHECK(hwy::IsAligned(bytes_span.data(), imfy::memory_alignment_size));
	CHECK(*bytes_span.data() == initial_value);

	auto writable_span = span.as_writable_bytes();
	constexpr std::uint16_t set_value{0xAAU};
	*writable_span.data() = set_value;
	CHECK(array_input[0U] == set_value);
}