/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/concurrent_queue.hpp>
#include <imfy/fundamental.hpp>

#include <chrono>
#include <string>
#include <string_view>
#include <vector>

namespace imfy::report
{

enum class level : uint8_t
{
	trace,
	info,
	warn,
	error,
	critical,
};

class logger final
{
public:
	using token_t = moodycamel::ProducerToken;
	explicit logger(level min_level);
	~logger() = default;

	logger(const logger&) = delete;
	logger(logger&&) = default;
	logger& operator=(const logger&) = delete;
	logger& operator=(logger&&) = default;

	token_t create_token();
	void add_log(const token_t& token, level lvl, std::string_view text);
	[[nodiscard]] bool pending_logs() const;
	void take_logs(std::vector<std::string>& container);

private:
	using clock = std::chrono::steady_clock;
	moodycamel::ConcurrentQueue<std::string> _logs;
	moodycamel::ConsumerToken _token;
	clock::time_point _start_time;
	uint8_t _min_level{0U};
};

}
