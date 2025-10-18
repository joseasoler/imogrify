/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Operative system preprocessor defines.")
{
	STATIC_REQUIRE(IMOGRIFY_OS_LINUX + IMOGRIFY_OS_WINDOWS <= 1U);
}

TEST_CASE("Compiler preprocessor defines")
{
	STATIC_REQUIRE(IMOGRIFY_COMPILER_CLANG + IMOGRIFY_COMPILER_GCC + IMOGRIFY_COMPILER_MSVC <= 1U);

#if IMOGRIFY_COMPILER_MSVC
#if !defined(UNICODE) || !defined(_UNICODE)
	STATIC_REQUIRE(false);
#endif
#if defined(_MSVC_TRADITIONAL) && _MSVC_TRADITIONAL != 0
	STATIC_REQUIRE(false);
#endif

#endif
}

TEST_CASE("CMake option preprocessor defines")
{
	STATIC_REQUIRE(std::is_same_v<decltype(IMOGRIFY_SHOW_DEBUG_LOGS), bool>);
	STATIC_REQUIRE(std::is_same_v<decltype(IMOGRIFY_USE_LIBASSERT), bool>);
	STATIC_REQUIRE(std::is_same_v<decltype(IMOGRIFY_USE_LIBCPUID), bool>);
}
