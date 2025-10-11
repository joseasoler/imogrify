/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/arguments.hpp>
#include <imfy/arguments_parse.hpp>
#include <imfy/exit_status.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/platform.hpp>
#include <imfy/report_utility.hpp>

#include <fmt/base.h>

#include <exception>
#include <span>
#include <sstream>

namespace
{

using imfy::core::exit_status;

[[nodiscard]] int get_exit_code(const exit_status status) noexcept
{
	return static_cast<int>(status);
}

int imogrify_main(std::span<const char*> args)
{
	if (const char* error_message = imfy::core::platform::initialize(); error_message != nullptr)
	{
		fmt::println(stderr, "{:s}", error_message);
		return get_exit_code(exit_status::platform_initialization_failed);
	}

	const auto result = imfy::arguments::parse(args);
	using imfy::core::exit_status;
	if (!result.has_value())
	{
		return get_exit_code(result.error());
	}

	const auto& argument_data = result.value();

	using imfy::arguments::report_type;
	if (argument_data.report != report_type::none)
	{
		std::ostringstream buffer;

		if (argument_data.report == report_type::version)
		{
			imfy::report::generate_version_report(buffer);
		}
		if (argument_data.report == report_type::build || argument_data.report == report_type::all)
		{
			imfy::report::generate_build_report(buffer);
		}
		if (argument_data.report == report_type::runtime || argument_data.report == report_type::all)
		{
			imfy::report::generate_runtime_report(buffer);
		}
		if (argument_data.report == report_type::dependencies || argument_data.report == report_type::all)
		{
			imfy::report::generate_dependencies_report(buffer);
		}

		fmt::print("{:s}", buffer.view());
		return get_exit_code(exit_status::success);
	}

	if (argument_data.help)
	{
		imfy::arguments::show_help();
		return get_exit_code(exit_status::success);
	}
	return get_exit_code(exit_status::success);
}

}

int main(const int argc, const char** argv)
{
	try
	{
		return imogrify_main(std::span<const char*>{argv, static_cast<imfy::size_t>(argc)});
	}
	catch (std::exception& exc)
	{
		fmt::println(stderr, "Uncaught exception: {:s}", exc.what());
		return get_exit_code(exit_status::unknown_error);
	}
	catch (...)
	{
		fmt::println(stderr, "Uncaught unknown exception.");
		return get_exit_code(exit_status::unknown_error);
	}
}
