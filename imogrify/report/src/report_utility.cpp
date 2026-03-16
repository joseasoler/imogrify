/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include "imfy/report_utility.hpp"

#include <imfy/assert.hpp>
#include <imfy/build.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/runtime.hpp>
#include <imfy/version.hpp>

#include <algorithm>
#include <array>
#include <iterator>
#include <optional>
#include <ostream>
#include <sstream>
#include <string_view>

namespace
{
using namespace imfy::core::build;

constexpr auto type_count = static_cast<imfy::size_t>(imfy::report::report_type::all) + 1U;

constexpr std::array<std::string_view, type_count> type_names{"none",					"version", "build",
																															"dependencies", "runtime", "all"};

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

void generate_version_report(std::ostringstream& buffer)
{
	buffer << project << '\n';
	buffer << list_prefix << "Homepage: " << project_homepage_url << '\n';
}

void generate_build_report(std::ostringstream& buffer)
{
	buffer << "Build:" << '\n';
	generate_version_report(buffer);
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
	if constexpr (imfy::core::runtime::available)
	{
		buffer << "Runtime:" << '\n';

		const auto [model, microarchitecture] = imfy::core::runtime::get_cpu_info();
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

}

namespace imfy::report
{

std::string_view type_to_str(const report_type rep_type) noexcept
{
	const auto index = static_cast<size_t>(rep_type);
	IMFY_ASSUME(index < type_count);
	return type_names[index];
}

std::optional<report_type> str_to_type(const std::string_view rep_str) noexcept
{
	const auto itr = std::ranges::find(type_names, rep_str);
	if (itr == std::cend(type_names))
	{
		return std::nullopt;
	}

	return static_cast<report_type>(std::distance(std::cbegin(type_names), itr));
}

void generate_report(const report_type report, std::ostringstream& buffer)
{
	if (report == report_type::version)
	{
		generate_version_report(buffer);
	}
	if (report == report_type::build || report == report_type::all)
	{
		generate_build_report(buffer);
	}
	if (report == report_type::runtime || report == report_type::all)
	{
		generate_runtime_report(buffer);
	}
	if (report == report_type::dependencies || report == report_type::all)
	{
		generate_dependencies_report(buffer);
	}
}

}
