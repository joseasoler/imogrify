/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/platform.hpp"

#if IMOGRIFY_OS_WINDOWS

#include <imfy/fundamental.hpp>

#include <cstdio>

// NOLINTNEXTLINE(misc-include-cleaner)
#include <Windows.h>
#endif

namespace imfy::core::platform
{

const char* initialize() noexcept
{
#if IMOGRIFY_OS_WINDOWS
	// NOLINTNEXTLINE(misc-include-cleaner)
	if (const auto console_output = static_cast<bool>(SetConsoleOutputCP(CP_UTF8)); !console_output)
	{
		return "UTF-8 encoding issue. Could not set terminal output code page to CP_UTF8.";
	}
	constexpr size_t buffer_size = 1024U;
	if (std::setvbuf(stdout, nullptr, _IOFBF, buffer_size) != 0)
	{
		return "UTF-8 encoding issue. Could not set standard output buffer size.";
	}
	if (std::setvbuf(stderr, nullptr, _IOFBF, buffer_size) != 0)
	{
		return "UTF-8 encoding issue. Could not set standard error buffer size.";
	}
#else
	return nullptr;
#endif
}

}
