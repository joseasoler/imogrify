/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <imfy/report_utility.hpp>

#include <sstream>

namespace imfy::arguments
{

struct arg_data final
{
	bool help{};
	report::report_type report{};
};

void generate_help(std::ostringstream& buffer);

}
