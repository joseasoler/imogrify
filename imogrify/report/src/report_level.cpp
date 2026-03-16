/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "imfy/report_level.hpp"

#include <imfy/assert.hpp>
#include <imfy/fundamental.hpp>

#include <array>
#include <string_view>

namespace
{

constexpr auto level_count = static_cast<imfy::size_t>(imfy::report::level::fatal) + 1U;

constexpr std::array<std::string_view, level_count> level_names{"trace", "info", "warn", "error", "halt", "fatal"};

}

namespace imfy::report
{

std::string_view level_name(const level lvl) noexcept
{
	const auto index = static_cast<size_t>(lvl);
	IMFY_ASSUME(index < level_count);
	return level_names[index];
}

}
