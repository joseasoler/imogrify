/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/character.hpp>

#include <string_view>

namespace imfy::arguments
{

class short_name_def final
{
public:
	explicit consteval short_name_def(const char snm)
		: _value{snm}
	{
	}

	[[nodiscard]] consteval bool valid() const noexcept
	{
		// short_name_def must be lower-case alphanumeric.
		return core::character::is_lc_aldigit(_value);
	}

	[[nodiscard]] constexpr char value() const noexcept { return _value; }

private:
	char _value;
};

inline constexpr const char dash{'-'};

class long_name_def final
{
public:
	explicit consteval long_name_def(const std::string_view lnm)
		: _value{lnm}
	{
	}

	[[nodiscard]] consteval bool valid() const noexcept
	{
		if (_value.size() < 3U)
		{
			// long_name_def must have three characters or more.
			return false;
		}

		using namespace core::character;

		if (!is_lc_alpha(_value.front()))
		{
			// long_name_def must start with a lower-case alphabetic character.
			return false;
		}

		char prev_character = _value.front();
		for (size_t index = 1U; index < _value.size(); ++index)
		{
			const auto curr_character = _value[index];
			if (!is_lc_aldigit(curr_character) && curr_character != dash)
			{
				// long_name_def must only contain lower-case alphanumeric characters or dashes.
				return false;
			}

			if (prev_character == dash && curr_character == dash)
			{
				// long_name_def must not contain two adjacent dashes.
				return false;
			}

			prev_character = curr_character;
		}

		// long_name_def cannot end with a dash.
		return _value.back() != dash;
	}

	[[nodiscard]] constexpr std::string_view value() const noexcept { return _value; }

private:
	std::string_view _value;
};

class help_def final
{
public:
	explicit consteval help_def(const std::string_view help)
		: _value{help}
	{
	}

	[[nodiscard]] consteval bool valid() const noexcept { return !_value.empty(); }

	[[nodiscard]] constexpr std::string_view value() const noexcept { return _value; }

private:
	std::string_view _value;
};

class arg_def final
{
public:
	consteval arg_def(const std::string_view lnm, const char snm, const std::string_view hlp)
		: _lnm{lnm}
		, _snm{snm}
		, _hlp{hlp}
	{
	}

	consteval arg_def(const std::string_view lnm, const std::string_view hlp)
		: _lnm{lnm}
		, _snm{'\0'}
		, _hlp{hlp}
	{
	}

	[[nodiscard]] consteval bool valid() const noexcept
	{
		return _lnm.valid() && (_snm.valid() || _snm.value() == '\0') && _hlp.valid();
	}

private:
	long_name_def _lnm;
	short_name_def _snm;
	help_def _hlp;
};

}
