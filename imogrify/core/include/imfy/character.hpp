/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace imfy::core::character
{

[[nodiscard]] constexpr bool is_lc_alpha(const char character)
{
	return 'a' <= character && character <= 'z';
}

[[nodiscard]] constexpr bool is_digit(const char character)
{
	return '0' <= character && character <= '9';
}

[[nodiscard]] constexpr bool is_lc_aldigit(const char character)
{
	return is_lc_alpha(character) || is_digit(character);
}

}
