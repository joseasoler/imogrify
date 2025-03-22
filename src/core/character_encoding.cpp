/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/character_encoding.hpp"

#include <tl/expected.hpp>

#include <string_view>

#if IMOGRIFY_OS_WINDOWS
#include <cstdio>

// NOLINTNEXTLINE(misc-include-cleaner)
#include <Windows.h>
#endif // IMOGRIFY_OS_WINDOWS

namespace imfy::character_encoding
{

tl::expected<void, std::string_view> initialize()
{
#if IMOGRIFY_OS_WINDOWS
	// NOLINTNEXTLINE(misc-include-cleaner)
	if (const auto console_output = static_cast<bool>(SetConsoleOutputCP(CP_UTF8)); !console_output)
	{
		return tl::unexpected<std::string_view>("UTF-8 encoding issue. Could not set terminal output code page to CP_UTF8."
		);
	}
	constexpr std::size_t buffer_size = 1024U;
	if (std::setvbuf(stdout, nullptr, _IOFBF, buffer_size) != 0)
	{
		return tl::unexpected<std::string_view>("UTF-8 encoding issue. Could not set standard output buffer size.");
	}
	if (std::setvbuf(stderr, nullptr, _IOFBF, buffer_size) != 0)
	{
		return tl::unexpected<std::string_view>("UTF-8 encoding issue. Could not set standard error output buffer size.");
	}
#endif // IMOGRIFY_OS_WINDOWS
	return {};
}

}
