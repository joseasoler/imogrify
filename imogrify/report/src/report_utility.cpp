/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/report_utility.hpp"

#include <imfy/build.hpp>
#include <imfy/version.hpp>

#include <ostream>
#include <sstream>
#include <string_view>

#include "imfy/runtime.hpp"

namespace
{
using namespace imfy::core::build;

constexpr std::string_view list_prefix = " · ";

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
	buffer << list_prefix << project << '\n';
	buffer << list_prefix << "OS: " << operative_system_name() << '\n';
	buffer << list_prefix << "Compiler: " << compiler_name() << " [" << compiler_version << ']' << '\n';
	buffer << list_prefix << "Build type: " << build_type << '\n';
}

void generate_dependencies_report(std::ostringstream& buffer)
{
	buffer << "Dependencies:" << '\n';
	for (const auto& dependency : dependencies)
	{
		buffer << list_prefix << dependency << '\n';
	}
}

void generate_runtime_report(std::ostringstream& buffer)
{
	if constexpr (!core::runtime::available)
	{
		return;
	}
	buffer << "Runtime:" << '\n';

	const auto [model, microarchitecture] = core::runtime::get_cpu_info();
	if (const bool error = model.empty(); !error)
	{
		buffer << list_prefix << "CPU Model: " << model << '\n';
		buffer << list_prefix << "CPU Microarchitecture: " << microarchitecture << '\n';
	}
	else
	{
		buffer << list_prefix << "CPU information error: " << microarchitecture << '\n';
	}
}

}
