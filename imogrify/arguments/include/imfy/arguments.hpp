/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/report_utility.hpp>

namespace imfy::arguments
{

struct arg_data final
{
	bool help{};
	report::report_type report{};
};

void show_help();

}
