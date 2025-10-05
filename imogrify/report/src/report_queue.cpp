/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/report_queue.hpp"

#include <imfy/assert.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/report_level.hpp>
#include <imfy/thread.hpp>

#include <fmt/format.h>

#include <iterator>
#include <string>
#include <string_view>
#include <vector>

namespace imfy::report
{

report_queue::report_queue(const level min_level)
	: _token{_logs}
	, _start_time{clock::now()}
	, _min_level{static_cast<uint8_t>(min_level)}
{
	[[maybe_unused]] constexpr auto uint_min_level = static_cast<uint8_t>(level::trace);
	[[maybe_unused]] constexpr auto uint_max_level = static_cast<uint8_t>(level::fatal);
	IMFY_ASSUME(uint_min_level <= _min_level && _min_level <= uint_max_level);
}

report_queue::report_token_t report_queue::create_token()
{
	return report_token_t{_logs};
}

void report_queue::make_report(const report_token_t& token, const level lvl, const std::string_view text)
{
	if (static_cast<uint8_t>(lvl) < _min_level)
	{
		return;
	}
	constexpr std::string_view format{"[{:d} ns] [@{:s}] [{:s}] {:s}"};
	const int64_t nanoseconds = (clock::now() - _start_time).count();
	_logs.enqueue(token, fmt::format(format, nanoseconds, this_thread::name(), level_name(lvl), text));
}

void report_queue::make_debug_report(
		[[maybe_unused]] const report_token_t& token, [[maybe_unused]] const level lvl,
		[[maybe_unused]] const std::string_view text
)
{
#if IMOGRIFY_SHOW_DEBUG_REPORTS || !defined(NDEBUG)
	make_report(token, lvl, text);
#endif
}

bool report_queue::pending_reports() const
{
	return _logs.size_approx() > 0U;
}

void report_queue::take_reports(std::vector<std::string>& container)
{
	const auto max = _logs.size_approx();
	_logs.try_dequeue_bulk(_token, std::back_inserter(container), max);
}

}
