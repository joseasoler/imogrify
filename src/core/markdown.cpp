/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/markdown.hpp"

#include <imfy/build.hpp>
#include <imfy/runtime.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <fmt/format.h>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string_view>
#include <utility>

namespace
{

constexpr auto bullet_text_description = " * **{:s}:** {:s}\n\n";

}

namespace imfy
{

/** An empty last row is used to signal that the table's real last row is complete. */
markdown_table::markdown_table()
	: data_(1U)
{
}

void markdown_table::add_cell_str(string value)
{
	const std::size_t index = data_.back().size();
	if (width_.size() < index + 1U)
	{
		width_.emplace_back(0U);
	}
	auto& width = width_[index];
	width = value.size() > width ? value.size() : width;
	data_.back().emplace_back(std::move(value));
}

void markdown_table::add_cell_str(std::string_view value)
{
	add_cell_str(std::string{value});
}

void markdown_table::add_cell_uint(std::uint64_t value)
{
	add_cell_str(fmt::format("{:d}", value));
}

void markdown_table::add_cell_double(double value, std::string_view postfix)
{
	add_cell_str(fmt::format("{:.1Lf}{:s}", value, postfix));
}

void markdown_table::end_row()
{
	// Create an empty row at the end. This signal that the previous row is over, and prepares the table for further
	// insertions.
	data_.emplace_back();
}

vector<std::size_t> markdown_table::width() const noexcept
{
	return width_;
}
vector<vector<string>> markdown_table::data() const noexcept
{
	return data_;
}

markdown::markdown(std::ostream& output)
	: output_{output}
{
}

void markdown::add_heading(const heading level, const std::string_view text)
{
	output_ << fmt::format("{0:#>{1}} {2}\n\n", "", static_cast<int>(level), text);
}

void markdown::add_build_information(heading level)
{
	add_heading(level, "Build information");

	constexpr auto bullet_version_description = " * **{:s}:** {:d}.{:d}.{:d}\n\n";

	using namespace imfy::build;
	output_ << fmt::format(
			bullet_version_description, project.name, project.version.major, project.version.minor, project.version.patch
	);

	output_ << fmt::format(bullet_text_description, "Build type", build_type);
	output_ << fmt::format(
			" * **Compiler:** {:s} {:d}.{:d}.{:d}\n\n", compiler_name(), compiler_version.major, compiler_version.minor,
			compiler_version.patch
	);

	const auto next_level = static_cast<heading>(static_cast<std::uint8_t>(level) + 1);
	add_heading(next_level, "Dependencies");
	for (const auto& dependency : dependencies)
	{
		if (dependency.use != dependency_use::imogrify)
		{
			continue;
		}

		output_ << fmt::format(
				" * **{:s}:** {:d}.{:d}.{:d}\n\n", dependency.name, dependency.version.major, dependency.version.minor,
				dependency.version.patch
		);
	}
}

void markdown::add_runtime_information([[maybe_unused]] heading level)
{
	const auto cpu_information_result = runtime::cpu_information();
	if (!cpu_information_result.has_value())
	{
		return;
	}
	add_heading(level, "Runtime information");
	const auto& [brand, microarchitecture, features] = cpu_information_result.value();

	output_ << fmt::format(bullet_text_description, "CPU brand", brand);
	output_ << fmt::format(bullet_text_description, "CPU microarchitecture", microarchitecture);

	output_ << " * **CPU features:** ";
	bool first = true;
	for (const auto& feature : features)
	{
		if (!first) [[likely]]
		{
			output_ << ", ";
		}
		first = false;
		output_ << feature;
	}
	output_ << "\n\n";
}

void markdown::add_table(const markdown_table& table)
{
	const auto& width = table.width();
	const auto& data = table.data();

	for (std::size_t row_index{0U}; row_index < data.size(); ++row_index)
	{
		const auto& row = data[row_index];
		if (row.empty())
		{
			break;
		}

		constexpr std::size_t padding = 2U;
		for (std::size_t cell_index{0U}; cell_index < width.size(); ++cell_index)
		{
			output_ << fmt::format("|{0: ^{1}}", row[cell_index], width[cell_index] + padding);
		}
		output_ << "|\n";

		if (row_index == 0U)
		{
			// Header separator line.
			for (const std::size_t current_width : width)
			{
				output_ << fmt::format("|{0:->{1}}", "", current_width + padding);
			}
			output_ << "|\n";
		}
	}

	output_ << "\n";
}

}
