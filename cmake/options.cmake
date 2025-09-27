# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

option(IMOGRIFY_BUILD_UNIT_TESTS "Build unit tests" OFF)
option(IMOGRIFY_CLANG_TIDY "Analyze the project with clang-tidy" OFF)
option(IMOGRIFY_USE_LIBASSERT "Implement asserts using libassert" OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	option(IMOGRIFY_CLANG_ALL_WARNINGS
		"Include most Clang warnings. This may trigger unexpected positives when using newer Clang versions" OFF)
endif ()
