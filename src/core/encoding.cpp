/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/encoding.hpp"

#if IMOGRIFY_OS_WINDOWS
#include <cstdio>

// NOLINTNEXTLINE(misc-include-cleaner)
#include <Windows.h>
#endif // IMOGRIFY_OS_WINDOWS

namespace imfy
{

bool initialize_encoding()
{
#if IMOGRIFY_OS_WINDOWS
	// NOLINTNEXTLINE(misc-include-cleaner)
	SetConsoleOutputCP(CP_UTF8);
	constexpr std::size_t buffer_size = 1024U;
	return std::setvbuf(stdout, nullptr, _IOFBF, buffer_size) == 0 &&
				 std::setvbuf(stderr, nullptr, _IOFBF, buffer_size) == 0;
#else
	return true;
#endif // IMOGRIFY_OS_WINDOWS
}

}
