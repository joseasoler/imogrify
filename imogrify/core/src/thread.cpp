/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/thread.hpp"

#include <fmt/format.h>
// Header required for the std::thread::id formatter.
// NOLINTNEXTLINE(misc-include-cleaner)
#include <fmt/std.h>

#include <string>
#include <thread>
#include <utility>

namespace
{

std::string& thread_name()
{
	thread_local std::string name{fmt::format("{}", std::this_thread::get_id())};
	return name;
}

}

namespace imfy::this_thread
{

void set_name(std::string name)
{
	thread_name() = std::move(name);
}

const std::string& name()
{
	return thread_name();
}

}
