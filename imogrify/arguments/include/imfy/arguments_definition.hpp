/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/arguments.hpp>
#include <imfy/character.hpp>
#include <imfy/fundamental.hpp>

#include <tl/expected.hpp>

#include <algorithm>
#include <span>
#include <string_view>
#include <vector>

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
	using result_t = tl::expected<void, std::string_view>;
	using set_flag_func_t = result_t (*)(arg_data&);
	using parse_next_func_t = result_t (*)(const char*, arg_data&);

	consteval arg_def(
			const std::string_view lnm, const char snm, const std::string_view hlp, const set_flag_func_t set_flag
	)
		: _lnm{lnm}
		, _snm{snm}
		, _hlp{hlp}
		, _set_flag_func{set_flag}
		, _parse_next_func{nullptr}
	{
	}

	consteval arg_def(const std::string_view lnm, const std::string_view hlp, const set_flag_func_t set_flag)
		: arg_def{lnm, '\0', hlp, set_flag}
	{
	}

	consteval arg_def(
			const std::string_view lnm, const char snm, const std::string_view hlp, const parse_next_func_t parse_next
	)
		: _lnm{lnm}
		, _snm{snm}
		, _hlp{hlp}
		, _set_flag_func{nullptr}
		, _parse_next_func{parse_next}
	{
	}

	consteval arg_def(const std::string_view lnm, const std::string_view hlp, const parse_next_func_t parse_next)
		: arg_def{lnm, '\0', hlp, parse_next}
	{
	}

	[[nodiscard]] consteval bool valid() const noexcept
	{
		return _lnm.valid() && (_snm.valid() || _snm.value() == '\0') && _hlp.valid();
	}

	[[nodiscard]] constexpr std::string_view long_name() const noexcept { return _lnm.value(); }
	[[nodiscard]] constexpr char short_name() const noexcept { return _snm.value(); }
	[[nodiscard]] constexpr std::string_view help() const noexcept { return _hlp.value(); }
	[[nodiscard]] constexpr set_flag_func_t set_flag_func() const noexcept { return _set_flag_func; }
	[[nodiscard]] constexpr parse_next_func_t parse_next_func() const noexcept { return _parse_next_func; }

private:
	long_name_def _lnm;
	short_name_def _snm;
	help_def _hlp;
	set_flag_func_t _set_flag_func;
	parse_next_func_t _parse_next_func;
};

[[nodiscard]] consteval bool validate_argument_definitions(const std::span<const arg_def> arg_defs)
{
	std::vector<std::string_view> long_names{};
	std::vector<char> short_names{};
	std::vector<arg_def::set_flag_func_t> set_flags{};
	std::vector<arg_def::parse_next_func_t> parse_nexts{};

	for (const auto& def : arg_defs)
	{
		if (!def.valid())
		{
			return false;
		}

		if (std::ranges::find(long_names, def.long_name()) != long_names.cend())
		{
			return false;
		}
		long_names.emplace_back(def.long_name());

		if (const auto short_name = def.short_name(); short_name != '\0')
		{
			if (std::ranges::find(short_names, short_name) != short_names.cend())
			{
				return false;
			}
			short_names.emplace_back(short_name);
		}

		if (const auto set_flag_func = def.set_flag_func(); set_flag_func != nullptr)
		{
			if (std::ranges::find(set_flags, set_flag_func) != set_flags.cend())
			{
				return false;
			}
			set_flags.emplace_back(set_flag_func);
		}

		if (const auto parse_next_func = def.parse_next_func(); parse_next_func != nullptr)
		{
			if (std::ranges::find(parse_nexts, parse_next_func) != parse_nexts.cend())
			{
				return false;
			}
			parse_nexts.emplace_back(parse_next_func);
		}
	}
	return true;
}

}
