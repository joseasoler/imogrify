/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Operative system preprocessor defines.")
{
	static_assert(IMOGRIFY_OS_LINUX + IMOGRIFY_OS_WINDOWS <= 1U);
}

TEST_CASE("Compiler preprocessor defines.")
{
	static_assert(IMOGRIFY_COMPILER_CLANG + IMOGRIFY_COMPILER_GCC + IMOGRIFY_COMPILER_MSVC <= 1U);

#if IMOGRIFY_COMPILER_MSVC
#if !defined(UNICODE) || !defined(_UNICODE)
	static_assert(false, "Unicode and UTF-8 support must be enabled when using MSVC.");
#endif
#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL != 0
	static_assert(false, "Preprocessor conformance mode must be enabled when using MSVC.");
#endif

#endif
}

TEST_CASE("CMake option preprocessor defines.")
{
	// NOLINTBEGIN(misc-redundant-expression)

#if !defined(IMOGRIFY_SHOW_DEBUG_REPORTS)
	static_assert(false, "CMake error, IMOGRIFY_SHOW_DEBUG_REPORTS is undefined.");
#else
	static_assert(IMOGRIFY_SHOW_DEBUG_REPORTS == 0 || IMOGRIFY_SHOW_DEBUG_REPORTS == 1);
#endif

#if !defined(IMOGRIFY_USE_LIBASSERT)
	static_assert(false, "CMake error, IMOGRIFY_USE_LIBASSERT is undefined.");
#else
	static_assert(IMOGRIFY_USE_LIBASSERT == 0 || IMOGRIFY_USE_LIBASSERT == 1);
#endif

#if !defined(IMOGRIFY_USE_LIBCPUID)
	static_assert(false, "CMake error, IMOGRIFY_USE_LIBCPUID is undefined.");
#else
	static_assert(IMOGRIFY_USE_LIBCPUID == 0 || IMOGRIFY_USE_LIBCPUID == 1);
#endif

	// NOLINTEND(misc-redundant-expression)
}
