/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/concepts.hpp"

#include <imfy/allocator.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <array>
#include <cstdint>
#include <memory>

#include <doctest/doctest.h>

namespace
{
struct simple_struct
{
	std::int64_t first_value;
	std::int8_t second_value;
};

struct inheritance_struct final : public simple_struct
{
	std::int8_t third_value;
};

} // namespace

TEST_CASE("Plain old object concept.")
{
	static_assert(imfy::pod_type<std::uint8_t>);
	// NOLINTNEXTLINE(cppcoreguidelines-avoid-c-arrays,hicpp-avoid-c-arrays,modernize-avoid-c-arrays)
	static_assert(imfy::pod_type<std::uint8_t[]>);
	static_assert(imfy::pod_type<std::array<std::uint8_t, 4U>>);
	static_assert(imfy::pod_type<simple_struct>);
	static_assert(!imfy::pod_type<inheritance_struct>);
	static_assert(!imfy::pod_type<imfy::vector<std::uint8_t>>);
	static_assert(!imfy::pod_type<imfy::string>);
	static_assert(!imfy::pod_type<std::unique_ptr<std::uint8_t>>);
}

TEST_CASE("standard_allocator concept")
{
	static_assert(imfy::standard_empty_allocator<std::allocator<int>>);
	static_assert(imfy::standard_empty_allocator<imfy::allocator<int>>);
}