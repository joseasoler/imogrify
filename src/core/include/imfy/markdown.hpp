/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <cstdint>
#include <ios>
#include <span>
#include <string_view>

namespace imfy
{

class markdown_table final
{
public:
	markdown_table();
	markdown_table(const markdown_table&) = delete;
	markdown_table(markdown_table&&) noexcept = default;
	markdown_table& operator=(const markdown_table&) = delete;
	markdown_table& operator=(markdown_table&&) noexcept = default;
	~markdown_table() = default;

	void add_cell_str(string value);
	void add_cell_str(std::string_view value);
	void add_cell_uint(std::uint64_t value);
	void add_cell_double(double value, std::string_view postfix);
	void end_row();

	[[nodiscard]] vector<std::size_t> width() const noexcept;
	[[nodiscard]] vector<vector<string>> data() const noexcept;

private:
	vector<std::size_t> width_;
	vector<vector<string>> data_;
};

class markdown final
{
public:
	explicit markdown(std::ostream& output);
	markdown() = delete;
	markdown(const markdown&) = delete;
	markdown(markdown&&) noexcept = delete;
	markdown& operator=(const markdown&) = delete;
	markdown& operator=(markdown&&) noexcept = delete;
	~markdown() = default;

	enum class heading : std::uint8_t
	{
		level_1 = 1U,
		level_2,
		level_3,
		level_4,
		level_5,
		level_6,
	};

	void add_heading(heading level, std::string_view text);

	void add_build_information(heading level);
	void add_runtime_information(heading level);

	void add_table(const markdown_table& table);

private:
	std::ostream& output_;
};

}
