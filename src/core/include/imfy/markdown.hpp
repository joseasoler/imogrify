/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>
#include <ios>
#include <span>
#include <string_view>

namespace imfy
{

namespace detail
{
constexpr std::uint8_t cell_padding = 2U;
} // namespace detail

template <std::size_t row_cell_count>
consteval std::array<std::uint8_t, row_cell_count> get_cell_width(
		const std::array<std::uint8_t, row_cell_count>& data_width,
		const std::array<std::string_view, row_cell_count>& header
)
{
	std::array<std::uint8_t, row_cell_count> cell_width{};

	for (std::size_t cell_index{0U}; cell_index < cell_width.size(); ++cell_index)
	{
		const auto header_text_width = static_cast<std::uint8_t>(header[cell_index].size());
		const auto max_width =
				data_width[cell_index] > header[cell_index].size() ? data_width[cell_index] : header_text_width;
		cell_width[cell_index] = max_width + detail::cell_padding;
		if (cell_width[cell_index] % 2U != header_text_width % 2U)
		{
			++cell_width[cell_index];
		}
	}

	return cell_width;
}

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

	void add_table_header(std::span<const std::uint8_t> cell_width, std::span<const std::string_view> header);
	void add_table_cell(uint8_t cell_width, std::string_view cell);
	void add_table_percent(uint8_t cell_width, double cell_value);
	void add_table_unsigned(uint8_t cell_width, std::uint64_t cell_value);
	void end_table_row();
	void end_table();

private:
	std::ostream& output_;
};

} // namespace imfy
