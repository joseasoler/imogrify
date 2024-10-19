/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/markdown.hpp"

#include <string_view>

#include <doctest.h>

using imfy::markdown;
using namespace std::string_view_literals;

TEST_CASE("Markdown headers")
{
	SUBCASE("Level 1")
	{
		markdown mark;
		mark.add_heading(markdown::heading::level_1, "Test"sv);
		CHECK((mark.view() == "# Test\n\n"sv));
	}
	SUBCASE("Level 4")
	{
		markdown mark;
		mark.add_heading(markdown::heading::level_4, "Test"sv);
		CHECK((mark.view() == "#### Test\n\n"sv));
	}
}