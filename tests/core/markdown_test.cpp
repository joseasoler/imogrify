/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/markdown.hpp"

#include <catch2/catch_test_macros.hpp>
#include <string_view>

using imfy::markdown;
using namespace std::string_view_literals;

TEST_CASE("Markdown headers", "[core][markdown]")
{
	SECTION("Level 1")
	{
		markdown mark;
		mark.add_heading(markdown::heading::level_1, "Test"sv);
		REQUIRE(mark.view() == "# Test\n\n"sv);
	}
	SECTION("Level 4")
	{
		markdown mark;
		mark.add_heading(markdown::heading::level_4, "Test"sv);
		REQUIRE(mark.view() == "#### Test\n\n"sv);
	}
}