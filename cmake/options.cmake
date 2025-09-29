# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

option(IMOGRIFY_BUILD_UNIT_TESTS "Build unit tests" OFF)
option(IMOGRIFY_CLANG_TIDY "Analyze the project with clang-tidy" OFF)
option(IMOGRIFY_CMAKE_VERBOSE "Show additional information during CMake configuration" OFF)
option(IMOGRIFY_SHOW_DEBUG_REPORTS "Display debug reports on release builds" OFF)
option(IMOGRIFY_USE_LIBASSERT "Implement asserts using libassert" OFF)
option(IMOGRIFY_USE_LIBCPUID "Implement CPU runtime information using libcpuid" OFF)

if (IMOGRIFY_CMAKE_VERBOSE)
	message(STATUS "CMake options:"
			"\n · CMAKE_COMPILE_WARNING_AS_ERROR ${CMAKE_COMPILE_WARNING_AS_ERROR}"
			"\n · IMOGRIFY_BUILD_UNIT_TESTS      ${IMOGRIFY_BUILD_UNIT_TESTS}"
			"\n · IMOGRIFY_CLANG_TIDY            ${IMOGRIFY_CLANG_TIDY}"
			"\n · IMOGRIFY_CMAKE_VERBOSE         ${IMOGRIFY_CMAKE_VERBOSE}"
			"\n · IMOGRIFY_SHOW_DEBUG_REPORTS    ${IMOGRIFY_SHOW_DEBUG_REPORTS}"
			"\n · IMOGRIFY_USE_LIBASSERT         ${IMOGRIFY_USE_LIBASSERT}"
			"\n · IMOGRIFY_USE_LIBCPUID          ${IMOGRIFY_USE_LIBCPUID}"
	)
endif ()