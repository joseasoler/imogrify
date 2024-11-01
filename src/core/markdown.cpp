/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/markdown.hpp"

#include <imfy/build.hpp>

#include <fmt/format.h>
#include <magic_enum.hpp>

#include <cstddef>
#include <cstdint>
#include <iostream>
#include <span>
#include <string_view>

using namespace std::string_view_literals;

namespace
{
constexpr auto table_row_end = "|\n"sv;

constexpr auto table_cell_format = "|{0: ^{1}}"sv;

} // Anonymous namespace

namespace imfy
{

markdown::markdown(std::ostream& output)
	: output_{output}
{
}

void markdown::add_heading(const heading level, const std::string_view text)
{
	output_ << fmt::format("{0:#>{1}} {2}\n\n"sv, "", static_cast<int>(level), text);
}

void markdown::add_build_information(heading level)
{
	add_heading(level, "Build information");

	constexpr auto bullet_text_description = " * **{:s}:** {:s}\n\n";
	constexpr auto bullet_version_description = " * **{:s}:** {:d}.{:d}.{:d}\n\n";

	using namespace imfy::build;
	output_ << fmt::format(
			bullet_version_description, imfy::build::project.name, imfy::build::project.version.major, project.version.minor,
			imfy::build::project.version.patch
	);

	output_ << fmt::format(bullet_text_description, "Build type", build_type);
	output_ << fmt::format(
			" * **Compiler:** {:s} {:d}.{:d}.{:d}\n\n", magic_enum::enum_name(compiler), compiler_version.major,
			compiler_version.minor, compiler_version.patch
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

void markdown::add_table_header(
		const std::span<const std::uint8_t> cell_width, const std::span<const std::string_view> header
)
{
	constexpr auto header_line_format = "|{0:->{1}}"sv;

	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		output_ << fmt::format(table_cell_format, header[cell_index], cell_width[cell_index]);
	}
	output_ << table_row_end;
	for (const std::size_t current_width : cell_width)
	{
		output_ << fmt::format(header_line_format, ""sv, current_width);
	}
	output_ << table_row_end;
}

void markdown::add_table_cell(const uint8_t cell_width, const std::string_view cell)
{
	output_ << fmt::format(table_cell_format, cell, cell_width);
}

void markdown::add_table_percent(uint8_t cell_width, double cell_value)
{
	constexpr auto format_percent = "{:.1Lf}%"sv;
	add_table_cell(cell_width, fmt::format(format_percent, cell_value, cell_width));
}

void markdown::add_table_unsigned(uint8_t cell_width, std::uint64_t cell_value)
{
	constexpr auto format_unsigned = "{:d}"sv;
	add_table_cell(cell_width, fmt::format(format_unsigned, cell_value, cell_width));
}

void markdown::end_table_row()
{
	output_ << table_row_end;
}

void markdown::end_table()
{
	output_ << '\n';
}

} // namespace imfy
