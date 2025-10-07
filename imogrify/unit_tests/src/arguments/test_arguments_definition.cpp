/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/arguments_definition.hpp"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("short_name_def")
{
	using imfy::arguments::short_name_def;
	STATIC_REQUIRE(short_name_def{'a'}.valid());
	STATIC_REQUIRE(short_name_def{'8'}.valid());

	STATIC_REQUIRE(!short_name_def{'A'}.valid());
	STATIC_REQUIRE(!short_name_def{' '}.valid());
	STATIC_REQUIRE(!short_name_def{'\t'}.valid());
	STATIC_REQUIRE(!short_name_def{'#'}.valid());
	STATIC_REQUIRE(!short_name_def{'-'}.valid());
}

TEST_CASE("long_name_def")
{
	using imfy::arguments::long_name_def;
	STATIC_REQUIRE(long_name_def{"word"}.valid());
	STATIC_REQUIRE(long_name_def{"two-words"}.valid());
	STATIC_REQUIRE(long_name_def{"this-1-has-multiple-words"}.valid());
	STATIC_REQUIRE(long_name_def{"quality-8"}.valid());

	STATIC_REQUIRE(!long_name_def{"conTains-upper-case"}.valid());
	STATIC_REQUIRE(!long_name_def{"2-starts-with-digit"}.valid());
	STATIC_REQUIRE(!long_name_def{"multiple--dashes"}.valid());
	STATIC_REQUIRE(!long_name_def{"end-with-dash-"}.valid());
	STATIC_REQUIRE(!long_name_def{"-starts-with-dash"}.valid());
}

TEST_CASE("help_def")
{
	using imfy::arguments::help_def;
	STATIC_REQUIRE(help_def{"word"}.valid());
	STATIC_REQUIRE(!help_def{""}.valid());
}
