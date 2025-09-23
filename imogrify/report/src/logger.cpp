/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/logger.hpp"

#include <imfy/fundamental.hpp>

#include <fmt/format.h>

#include <array>
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
	: _min_level{static_cast<uint8_t>(min_level)}
{
}

void logger::add(const level lvl, const std::string_view text)
{
	if (static_cast<uint8_t>(lvl) < _min_level)
	{
		return;
	}
	constexpr std::string_view format{"[{:s}] {:s}"};
	_logs.emplace_back(fmt::format(format, level_names[static_cast<size_t>(lvl)], text));
}

std::vector<std::string> logger::take_all()
{
	std::vector<std::string> logs;
	std::swap(_logs, logs);
	return logs;
}

}
