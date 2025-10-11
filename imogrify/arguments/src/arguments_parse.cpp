/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/arguments_parse.hpp"

#include <imfy/arguments.hpp>
#include <imfy/arguments_definition.hpp>
#include <imfy/assert.hpp>
#include <imfy/exit_status.hpp>
#include <imfy/fundamental.hpp>

#include <fmt/base.h>
#include <tl/expected.hpp>

#include <array>
#include <limits>
#include <span>
#include <unordered_map>
#include <utility>

namespace
{
using def_result_t = imfy::arguments::arg_def::result_t;
using imfy::arguments::arg_data;

def_result_t set_help_flag(arg_data& data)
{
	data.help = true;
	return {};
}

def_result_t set_build_report_flag(arg_data& data)
{
	data.build_report = true;
	return {};
}

using imfy::arguments::arg_def;

consteval auto create_argument_definitions()
{
	constexpr auto argument_definitions = std::to_array(
			{arg_def{"help", 'h', "Show this help and exit.", set_help_flag},
			 arg_def{"build-report", "Report build metadata and runtime hardware.", set_build_report_flag}}
	);
	static_assert(imfy::arguments::validate_argument_definitions(argument_definitions));
	return argument_definitions;
}

constexpr auto argument_definitions = create_argument_definitions();

auto create_parser_maps()
{
	std::unordered_map<std::string_view, imfy::size_t> long_to_def{};
	std::unordered_map<char, imfy::size_t> short_to_def{};

	for (imfy::size_t index = 0U; index < argument_definitions.size(); ++index)
	{
		const auto& def = argument_definitions[index];
		IMFY_ASSUME(!long_to_def.contains(def.long_name()));
		long_to_def[def.long_name()] = index;
		IMFY_ASSUME(!short_to_def.contains(def.short_name()));
		short_to_def[def.short_name()] = index;
	}

	return std::make_pair(long_to_def, short_to_def);
}

constexpr auto invalid_def_index = std::numeric_limits<imfy::size_t>::max();

imfy::size_t get_def_index(
		const char* current_arg, const std::unordered_map<std::string_view, imfy::size_t>& long_to_def,
		std::unordered_map<char, imfy::size_t> short_to_def
)
{
	IMFY_ASSUME(current_arg != nullptr);

	const std::string_view raw_argument{current_arg};

	if (raw_argument.size() == 2U && raw_argument.front() == '-')
	{
		if (const auto itr = short_to_def.find(raw_argument[1U]); itr != short_to_def.cend())
		{
			return itr->second;
		}
	}
	else if (raw_argument.size() >= 3U && raw_argument[0] == '-' && raw_argument[1] == '-')
	{
		const std::string_view long_name{raw_argument.cbegin() + 2U, raw_argument.cend()};
		if (const auto itr = long_to_def.find(long_name); itr != long_to_def.cend())
		{
			return itr->second;
		}
	}

	return invalid_def_index;
}

}

namespace imfy::arguments
{

result_t parse(const std::span<const char*> arguments)
{
	const auto [long_to_def, short_to_def] = create_parser_maps();

	arg_data data{};
	size_t index = 1U;

	// Process flags and arguments.
	while (index < arguments.size())
	{
		const auto def_index = get_def_index(arguments[index], long_to_def, short_to_def);
		if (def_index == invalid_def_index)
		{
			fmt::println("Invalid argument {:s}", arguments[index]);
			return tl::make_unexpected(core::exit_status::wrong_cli_arguments);
		}

		IMFY_ASSUME(def_index < argument_definitions.size());
		const auto& def = argument_definitions[def_index];

		if (def.set_flag_func() != nullptr)
		{
			const auto result = def.set_flag_func()(data);
			if (!result.has_value())
			{
				fmt::println("Error in flag {:s}: {:s}", def.long_name(), result.error());
				return tl::make_unexpected(core::exit_status::wrong_cli_arguments);
			}
		}
		else
		{
			IMFY_ASSUME(def.parse_next_func() != nullptr);
			++index;
			const auto result = def.parse_next_func()(arguments[index], data);
			if (!result.has_value())
			{
				fmt::println("Error in argument {:s} {:s}: {:s}", def.long_name(), arguments[index], result.error());
				return tl::make_unexpected(core::exit_status::wrong_cli_arguments);
			}
		}

		++index;
	}

	return data;
}

}
