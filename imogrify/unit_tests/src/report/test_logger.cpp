/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/logger.hpp>

#include <concepts>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Logger type traits")
{
	using imfy::report::logger;
	static_assert(
			!std::is_default_constructible_v<logger>, "Creating a logger requires setting its min level explicitly."
	);
	static_assert(
			!std::is_copy_constructible_v<logger> && !std::is_copy_assignable_v<logger> && std::movable<logger>,
			"Logger is a move-only type."
	);
}

TEST_CASE("Basic test")
{
	using imfy::report::level;
	using imfy::report::logger;

	logger logs{level::info};
	logs.add(level::trace, "Test0");
	logs.add(level::info, "Test1");

	const auto data = logs.take_all();
	REQUIRE(data.size() == 1U);
}
