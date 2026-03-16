/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <imfy/fundamental.hpp>

#include <optional>
#include <sstream>

namespace imfy::report
{

enum class report_type : imfy::uint8_t
{
	none,
	version,
	build,
	dependencies,
	runtime,
	all
};

[[nodiscard]] std::string_view type_to_str(report_type rep_type) noexcept;

[[nodiscard]] std::optional<report_type> str_to_type(std::string_view rep_str) noexcept;

void generate_report(report_type report, std::ostringstream& buffer);

}
