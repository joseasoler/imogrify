/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <doctest/doctest.h>

TEST_CASE("Operative system preprocessor defines.")
{
	static_assert(IMOGRIFY_OS_LINUX + IMOGRIFY_OS_MACOS + IMOGRIFY_OS_WINDOWS <= 1U);
}

TEST_CASE("Compiler preprocessor defines.")
{
	static_assert(
			IMOGRIFY_COMPILER_APPLE_CLANG + IMOGRIFY_COMPILER_CLANG + IMOGRIFY_COMPILER_GCC + IMOGRIFY_COMPILER_INTEL_LLVM +
					IMOGRIFY_COMPILER_MSVC <=
			1U
	);

#if IMOGRIFY_COMPILER_MSVC
#if !defined(UNICODE) || !defined(_UNICODE)
	static_assert(false, "Unicode and UTF-8 support must be enabled when using MSVC.");
#endif
#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL != 0
	static_assert(false, "Preprocessor conformance mode must be enabled when using MSVC.");
#endif

#endif
}

TEST_CASE("Other defines.")
{
#if !defined(IMOGRIFY_USE_FMT_BASE_HEADER)
	static_assert(false, "IMOGRIFY_USE_FMT_BASE_HEADER is not configured correctly..");
#endif

#if !defined(IMOGRIFY_USE_LIBASSERT)
	static_assert(false, "IMOGRIFY_USE_LIBASSERT is not configured correctly.");
#endif
}
