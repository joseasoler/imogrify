/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/arguments.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/platform.hpp>
#include <imfy/report_utility.hpp>

#include <fmt/base.h>

#include <cstdlib>
#include <exception>
#include <span>
#include <sstream>
#include <variant>

namespace
{

/** Imogrify-specific exit status codes. Avoid exit codes with specific meanings on bash and sysexits.h on Linux. */
// NOLINTNEXTLINE(readability-enum-initial-value)
enum class exit_status : imfy::uint8_t
{
	success = static_cast<imfy::uint8_t>(EXIT_SUCCESS),				// Everything went fine.
	general_error = static_cast<imfy::uint8_t>(EXIT_FAILURE), // Prefer more specific exit codes when possible.
	bash_shell_misuse = 2U,																		// Avoided as it has special meaning on bash.
	platform_initialization_failed,														// imogrify platform-specific initialization has failed.
	max_allowed_code = 63U,																		// First code used by sysexits.h.
};

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
	if (std::holds_alternative<imfy::arguments::parse_exit_code>(result))
	{
		return std::get<imfy::arguments::parse_exit_code>(result).exit_code;
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
	}
	catch (...)
	{
		fmt::println(stderr, "Uncaught unknown exception.");
	}
}
