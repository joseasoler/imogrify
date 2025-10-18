/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/log_queue.hpp"

#include <imfy/assert.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/log_level.hpp>

#include <concurrentqueue/moodycamel/concurrentqueue.h>
#include <enchantum_single_header.hpp>
#include <fmt/format.h>

#include <iterator>
#include <string>
#include <string_view>
#include <vector>

namespace imfy::pipeline
{

using report::log_level;

log_queue::log_queue(const log_level min_level)
	: _start_time{clock::now()}
	, _min_level{static_cast<uint8_t>(min_level)}
#if !defined(NDEBUG)
	, _generated_consumer_token{false}
#endif
{
	[[maybe_unused]] constexpr auto uint_min_level = static_cast<uint8_t>(log_level::trace);
	[[maybe_unused]] constexpr auto uint_max_level = static_cast<uint8_t>(log_level::fatal);
	IMFY_ASSUME(uint_min_level <= _min_level && _min_level <= uint_max_level);
}

log_queue::producer_token_t log_queue::create_producer_token()
{
	return {.value = moodycamel::ProducerToken{_logs}};
}

log_queue::consumer_token_t log_queue::create_consumer_token()
{
#if !defined(NDEBUG)
	IMFY_ASSERT(!_generated_consumer_token, "log_queue must not create multiple consumer tokens.");
	_generated_consumer_token = true;
#endif
	return {.value = moodycamel::ConsumerToken{_logs}};
}

void log_queue::add_log(
		const producer_token_t& token, const std::string_view worker_name, const log_level lvl, const std::string_view text
)
{
	if (static_cast<uint8_t>(lvl) < _min_level)
	{
		return;
	}
	constexpr std::string_view format{"[{:d} ns] [@{:s}] [{:s}] {:s}"};
	const int64_t nanoseconds = (clock::now() - _start_time).count();
	_logs.enqueue(token.value, fmt::format(format, nanoseconds, worker_name, enchantum::to_string(lvl), text));
}

void log_queue::add_debug_log(
		[[maybe_unused]] const producer_token_t& token, [[maybe_unused]] const std::string_view worker_name,
		[[maybe_unused]] const log_level lvl, [[maybe_unused]] const std::string_view text
)
{
#if IMOGRIFY_SHOW_DEBUG_LOGS || !defined(NDEBUG)
	add_log(token, worker_name, lvl, text);
#endif
}

bool log_queue::pending_logs(const consumer_token_t& /*token*/) const
{
	return _logs.size_approx() > 0U;
}

void log_queue::take_logs(consumer_token_t& token, std::vector<std::string>& container)
{
	const auto max = _logs.size_approx();
	_logs.try_dequeue_bulk(token.value, std::back_inserter(container), max);
}

}
