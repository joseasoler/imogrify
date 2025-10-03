/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/fundamental.hpp>
#include <imfy/report_level.hpp>
#include <imfy/report_queue.hpp>

#include <chrono>
#include <concepts>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <vector>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Report queue type traits")
{
	using imfy::report::report_queue;
	static_assert(
			!std::is_default_constructible_v<report_queue>, "Report queues must have a min level set during construction."
	);
	static_assert(
			!std::is_copy_constructible_v<report_queue> && !std::is_copy_assignable_v<report_queue> &&
					std::movable<report_queue>,
			"Report queue is a move-only type."
	);
}

TEST_CASE("Basic test")
{
	using imfy::report::level;
	using imfy::report::report_queue;

	report_queue logs{level::info};
	const auto token = logs.create_token();
	logs.make_report(token, level::trace, "test_0");
	constexpr std::string_view test_1{"test_1"};
	logs.make_report(token, level::info, "test_1");
	constexpr auto duration = std::chrono::microseconds(1);
	std::this_thread::sleep_for(duration);
	constexpr std::string_view test_2{"test_2"};
	logs.make_debug_report(token, level::info, test_2);

	std::vector<std::string> data;

	while (logs.pending_reports())
	{
		logs.take_reports(data);
	}
#if IMOGRIFY_SHOW_DEBUG_REPORTS || !defined(NDEBUG)
	constexpr imfy::size_t expected_report_count = 2U;
#else
	constexpr imfy::size_t expected_report_count = 1U;
#endif

	REQUIRE(data.size() == expected_report_count);
	const auto& first_log = data.front();
	REQUIRE(first_log.ends_with(test_1));
}
