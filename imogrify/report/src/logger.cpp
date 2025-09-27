/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/logger.hpp"

#include <imfy/fundamental.hpp>
#include <imfy/thread.hpp>

#include <fmt/format.h>

#include <array>
#include <iterator>
#include <string>
#include <string_view>
#include <vector>

namespace
{

constexpr std::array<std::string_view, static_cast<imfy::size_t>(imfy::report::level::critical) + 1U> level_names{
		"trace", "info", "warn", "error", "critical"
};

}

namespace imfy::report
{

logger::logger(const level min_level)
	: _token{_logs}
	, _start_time{clock::now()}
	, _min_level{static_cast<uint8_t>(min_level)}
{
}

logger::token_t logger::create_token()
{
	return token_t{_logs};
}

void logger::add_log(const token_t& token, const level lvl, const std::string_view text)
{
	if (static_cast<uint8_t>(lvl) < _min_level)
	{
		return;
	}
	constexpr std::string_view format{"[{:d} ns] [@{:s}] [{:s}] {:s}"};
	const int64_t nanoseconds = (clock::now() - _start_time).count();
	_logs.enqueue(
			token, fmt::format(format, nanoseconds, this_thread::name(), level_names[static_cast<size_t>(lvl)], text)
	);
}

bool logger::pending_logs() const
{
	return _logs.size_approx() > 0U;
}

void logger::take_logs(std::vector<std::string>& container)
{
	const auto max = _logs.size_approx();
	_logs.try_dequeue_bulk(_token, std::back_inserter(container), max);
}

}
