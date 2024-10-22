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
}
