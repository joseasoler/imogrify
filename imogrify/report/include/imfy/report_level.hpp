/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <imfy/fundamental.hpp>

#include <string_view>

namespace imfy::report
{

enum class level : uint8_t
{
	trace = 0U, // Detailed reports for the user. Not shown unless explicitly enabled.
	info,				// Standard reports for the user.
	warn,				// Minor errors which still allow the input to be processed.
	error,			// Error preventing one item from the input from being processed.
	halt,				// Request to stop the application. Items in progress will be finished first.
	fatal,			// Error preventing multiple items from being processed. imogrify will be terminated.
};

[[nodiscard]] std::string_view level_name(level lvl) noexcept;

}
