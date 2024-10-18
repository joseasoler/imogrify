/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

namespace imfy
{

class markdown final
{
public:
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

	void add_table(const std::vector<std::string_view>& header, const std::vector<std::vector<std::string>>& contents);

	[[nodiscard]] std::string_view view() const;

private:
	std::ostringstream output_;
};

} // namespace imfy