/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/character.hpp>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("is_lowercase_alpha static checks")
{
	using imfy::core::character::is_lc_alpha;
	STATIC_REQUIRE(is_lc_alpha('a'));
	STATIC_REQUIRE(is_lc_alpha('g'));
	STATIC_REQUIRE(is_lc_alpha('x'));
	STATIC_REQUIRE(!is_lc_alpha('A'));
	STATIC_REQUIRE(!is_lc_alpha('G'));
	STATIC_REQUIRE(!is_lc_alpha('X'));
	STATIC_REQUIRE(!is_lc_alpha('-'));
	STATIC_REQUIRE(!is_lc_alpha('4'));
}

TEST_CASE("is_digit static checks")
{
	using imfy::core::character::is_digit;
	STATIC_REQUIRE(is_digit('0'));
	STATIC_REQUIRE(is_digit('4'));
	STATIC_REQUIRE(is_digit('9'));
	STATIC_REQUIRE(!is_digit('a'));
	STATIC_REQUIRE(!is_digit('A'));
	STATIC_REQUIRE(!is_digit('-'));
}

TEST_CASE("is_lowercase_aldigit static checks")
{
	using imfy::core::character::is_lc_aldigit;
	static_assert(is_lc_aldigit('0'));
	static_assert(is_lc_aldigit('4'));
	static_assert(is_lc_aldigit('9'));
	static_assert(is_lc_aldigit('a'));
	static_assert(!is_lc_aldigit('A'));
	static_assert(!is_lc_aldigit('-'));
}
