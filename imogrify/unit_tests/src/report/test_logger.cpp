/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/logger.hpp>

#include <chrono>
#include <concepts>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <vector>

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
	const auto token = logs.create_token();
	logs.add_log(token, level::trace, "test_0");
	constexpr std::string_view test_1{"test_1"};
	logs.add_log(token, level::info, "test_1");
	constexpr auto duration = std::chrono::microseconds(1);
	std::this_thread::sleep_for(duration);
	constexpr std::string_view test_2{"test_2"};
	logs.add_log(token, level::info, test_2);

	std::vector<std::string> data;

	while (logs.pending_logs())
	{
		logs.take_logs(data);
	}
	REQUIRE(data.size() == 2U);
	const auto& first_log = data.front();
	REQUIRE(first_log.ends_with(test_1));
}
