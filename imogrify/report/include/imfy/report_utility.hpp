/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <sstream>

namespace imfy::report
{

void generate_version_report(std::ostringstream& buffer);
void generate_build_report(std::ostringstream& buffer);
void generate_dependencies_report(std::ostringstream& buffer);
void generate_runtime_report(std::ostringstream& buffer);

}
