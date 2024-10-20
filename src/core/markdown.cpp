/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/markdown.hpp"

#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <fmt/format.h>

#include <algorithm>
#include <cstddef>
#include <string_view>

using namespace std::string_view_literals;

namespace
{
imfy::vector<std::size_t> calculate_cell_width(
		const imfy::vector<std::string_view>& header, const imfy::vector<imfy::vector<imfy::string>>& contents
)
{
	constexpr std::size_t cell_padding = 2U;
	imfy::vector<std::size_t> cell_width(header.size(), 0U);
	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		cell_width[cell_index] = header[cell_index].size() + cell_padding;
	}

	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		for (const auto& row : contents)
		{
			cell_width[cell_index] = std::max(cell_width[cell_index], row[cell_index].size() + cell_padding);
		}
	}

	return cell_width;
}

} // Anonymous namespace

namespace imfy
{

void markdown::add_heading(const heading level, const std::string_view text)
{
	output_ << fmt::format("{0:#>{1}} {2}\n\n"sv, "", static_cast<int>(level), text);
}

void markdown::add_table(const vector<std::string_view>& header, const vector<vector<string>>& contents)
{
	const vector<std::size_t> cell_width = calculate_cell_width(header, contents);

	// Note that both formats add an extra character at the end for right padding.
	constexpr auto cell_format = "|{0: >{1}} "sv;
	constexpr auto header_separator_format = "|{0:->{1}}-"sv;
	constexpr auto row_end = "|\n"sv;

	for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
	{
		output_ << fmt::format(cell_format, header[cell_index], cell_width[cell_index]);
	}
	output_ << row_end;
	for (const std::size_t current_width : cell_width)
	{
		output_ << fmt::format(header_separator_format, ""sv, current_width);
	}
	output_ << row_end;

	for (const auto& row : contents)
	{
		for (std::size_t cell_index{}; cell_index < cell_width.size(); ++cell_index)
		{
			output_ << fmt::format(cell_format, row[cell_index], cell_width[cell_index]);
		}
		output_ << row_end;
	}
	output_ << '\n';
}

std::string_view markdown::view() const
{
	return output_.view();
}

} // namespace imfy
