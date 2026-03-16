/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <imfy/fundamental.hpp>

namespace imfy::core
{

/** Imogrify-specific exit status codes. Avoid exit codes with specific meanings on bash and sysexits.h on Linux. */
// NOLINTNEXTLINE(readability-enum-initial-value)
enum class exit_status : imfy::uint8_t
{
	success = 0U,										// Everything went fine.
	unknown_error = 1U,							// Prefer specific exit codes when possible.
	bash_shell_misuse = 2U,					// Avoided as it has special meaning on bash.
	platform_initialization_failed, // imogrify platform-specific initialization has failed.
	max_allowed_code = 63U,					// First code used by sysexits.h.
	wrong_cli_arguments = 64U,			// Command-line usage error.
};

}
