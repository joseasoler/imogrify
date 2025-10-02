/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <variant>

namespace imfy::arguments
{

struct data final
{
	bool build_report{};
};

struct parse_exit_code final
{
	int exit_code;
};

using result_t = std::variant<data, parse_exit_code>;

[[nodiscard]] result_t parse(int argc, const char** argv);

}
