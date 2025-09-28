/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/report_utility.hpp"

#include <imfy/build.hpp>
#include <imfy/version.hpp>

#include <ostream>
#include <sstream>

namespace
{
using namespace imfy::core::build;

[[nodiscard]] std::ostream& operator<<(std::ostream& oss, const version_t& version)
{
	oss << version.major << "." << version.minor << "." << version.patch;
	return oss;
}

[[nodiscard]] std::ostream& operator<<(std::ostream& oss, const dependency_t& dependency)
{
	oss << dependency.name << " [" << dependency.version << "]: " << dependency.description << " (" << dependency.license
			<< ')';
	return oss;
}

}

namespace imfy::report
{

void generate_build_report(std::ostringstream& buffer)
{
	buffer << "Build:" << '\n';
	buffer << '\t' << project << '\n';
	buffer << '\t' << "Compiler: " << compiler_name() << ' ' << compiler_version << '\n';
	buffer << '\t' << "Build type: " << build_type << '\n';
}

void generate_dependencies_report(std::ostringstream& buffer)
{
	buffer << "Dependencies:" << '\n';
	for (const auto& dependency : dependencies)
	{
		buffer << '\t' << dependency << '\n';
	}
}

}
