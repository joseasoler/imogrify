/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/fundamental.hpp>
#include <imfy/log_level.hpp>
#include <imfy/log_queue.hpp>

#include <chrono>
#include <string>
#include <string_view>
#include <thread>
#include <type_traits>
#include <vector>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Report queue type traits")
{
	using imfy::pipeline::log_queue;
	STATIC_REQUIRE(!std::is_default_constructible_v<log_queue>);
	STATIC_REQUIRE(!std::is_copy_constructible_v<log_queue>);
	STATIC_REQUIRE(!std::is_copy_assignable_v<log_queue>);
	STATIC_REQUIRE(!std::is_move_constructible_v<log_queue>);
	STATIC_REQUIRE(!std::is_move_assignable_v<log_queue>);
}

TEST_CASE("Basic test")
{
	using imfy::pipeline::log_queue;
	using imfy::report::log_level;

	log_queue logs{log_level::info};
	const auto producer_token = logs.create_producer_token();
	constexpr std::string_view worker_name = "unit_test";
	logs.add_log(producer_token, worker_name, log_level::trace, "test_0");
	constexpr std::string_view test_1{"test_1"};
	logs.add_log(producer_token, worker_name, log_level::info, "test_1");
	constexpr auto duration = std::chrono::microseconds(1);
	std::this_thread::sleep_for(duration);
	constexpr std::string_view test_2{"test_2"};
	logs.add_debug_log(producer_token, worker_name, log_level::info, test_2);

	std::vector<std::string> data;

	auto consumer_token = logs.create_consumer_token();
	while (logs.pending_logs(consumer_token))
	{
		logs.take_logs(consumer_token, data);
	}
#if IMOGRIFY_SHOW_DEBUG_LOGS || !defined(NDEBUG)
	constexpr imfy::size_t expected_report_count = 2U;
#else
	constexpr imfy::size_t expected_report_count = 1U;
#endif

	REQUIRE(data.size() == expected_report_count);
	const auto& first_log = data.front();
	REQUIRE(first_log.ends_with(test_1));
}
