/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
#endif
	return nullptr;
}

}
