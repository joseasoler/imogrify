/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
