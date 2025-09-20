/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/version.hpp>

#include <cstdint>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Type traits.")
{
	using imfy::core::build::version_t;
	static_assert(sizeof(version_t) < sizeof(std::uint64_t));
	static_assert(std::is_trivially_copyable_v<version_t> && std::is_standard_layout_v<version_t>);

	static_assert(version_t{}.major == 0U);
	static_assert(version_t{}.minor == 0U);
	static_assert(version_t{}.patch == 0U);
}
