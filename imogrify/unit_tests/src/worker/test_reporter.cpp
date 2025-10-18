/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/reporter.hpp>

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Reporter type traits")
{
	using imfy::worker::reporter;
	STATIC_REQUIRE(std::is_default_constructible_v<reporter>);
	STATIC_REQUIRE(!std::is_copy_constructible_v<reporter>);
	STATIC_REQUIRE(!std::is_copy_assignable_v<reporter>);
	STATIC_REQUIRE(std::is_move_constructible_v<reporter>);
	STATIC_REQUIRE(std::is_move_assignable_v<reporter>);
}
