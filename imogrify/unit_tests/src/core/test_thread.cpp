/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/thread.hpp>

#include <fmt/format.h>
// Header required for the std::thread::id formatter.
// NOLINTNEXTLINE(misc-include-cleaner)
#include <fmt/std.h>

#include <functional>
#include <string>
#include <thread>

#include <catch2/catch_test_macros.hpp>

namespace
{
void set_to_thread_name(std::string& thread_name)
{
	thread_name = imfy::this_thread::name();
}
}

TEST_CASE("Thread extensions")
{
	std::string thread_name{};
	std::thread thread_example(set_to_thread_name, std::ref(thread_name));
	thread_example.join();
	REQUIRE(!thread_name.empty());
	REQUIRE(thread_name != fmt::format("{}", std::this_thread::get_id()));
}
