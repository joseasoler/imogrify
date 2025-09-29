/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/fundamental.hpp>
#include <imfy/platform.hpp>
#include <imfy/report_utility.hpp>

#include <fmt/base.h>

#include <cstdlib>
#include <sstream>

namespace
{

/** Imogrify-specific exit status codes. Avoid exit codes with specific meanings on bash and sysexits.h on Linux. */
// NOLINTNEXTLINE(readability-enum-initial-value)
enum class exit_status : imfy::uint8_t
{
	success = EXIT_SUCCESS,					// Everything went fine.
	general_error = EXIT_FAILURE,		// Prefer more specific exit codes when possible.
	bash_shell_misuse = 2U,					// Avoided as it has special meaning on bash.
	platform_initialization_failed, // imogrify platform-specific initialization has failed.
	max_allowed_code = 63U,					// First code used by sysexits.h.
};

[[nodiscard]] int get_exit_code(const exit_status status)
{
	return static_cast<int>(status);
}

}

int main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv)
{
	if (const char* error_message = imfy::core::platform::initialize(); error_message != nullptr)
	{
		fmt::println(stderr, "{:s}", error_message);
		return get_exit_code(exit_status::platform_initialization_failed);
	}

	std::ostringstream buffer;
	imfy::report::generate_build_report(buffer);
	imfy::report::generate_dependencies_report(buffer);
	imfy::report::generate_runtime_report(buffer);
	fmt::print("{:s}", buffer.view());

	return get_exit_code(exit_status::success);
}
