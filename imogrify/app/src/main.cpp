/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/arguments.hpp>
#include <imfy/exit_status.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/platform.hpp>
#include <imfy/report_utility.hpp>

#include <fmt/base.h>

#include <cstdio>
#include <exception>
#include <span>
#include <sstream>
#include <variant>

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
	if (std::holds_alternative<exit_status>(result))
	{
		return get_exit_code(std::get<exit_status>(result));
	}

	const auto argument_data = std::get<imfy::arguments::data>(result);

	if (argument_data.build_report)
	{
		std::ostringstream buffer;
		imfy::report::generate_build_report(buffer);
		imfy::report::generate_runtime_report(buffer);
		imfy::report::generate_dependencies_report(buffer);
		fmt::print("{:s}", buffer.view());
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
