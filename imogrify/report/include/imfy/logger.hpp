/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

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
	explicit logger(level min_level);
	~logger() = default;

	logger(const logger&) = delete;
	logger(logger&&) = default;
	logger& operator=(const logger&) = delete;
	logger& operator=(logger&&) = default;

	void add(level lvl, std::string_view text);
	std::vector<std::string> take_all();

private:
	using clock = std::chrono::steady_clock;
	std::vector<std::string> _logs;
	clock::time_point _start_time;
	uint8_t _min_level{0U};
};

}
