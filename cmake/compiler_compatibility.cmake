# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

# Check for compiler versions. Set CMake variables for simpler compiler checking.
if (CMAKE_CXX_COMPILER_ID STREQUAL "AppleClang")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
		message(WARNING "${CMAKE_PROJECT_NAME} requires AppleClang 16 or newer.")
	endif ()
	set(IMOGRIFY_CXX_COMPILER_APPLE_CLANG 1)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 16)
		message(WARNING "${CMAKE_PROJECT_NAME} requires Clang 16 or newer.")
	endif ()
	set(IMOGRIFY_CXX_COMPILER_CLANG 1)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 11)
		message(WARNING "${CMAKE_PROJECT_NAME} requires GCC 11 or newer.")
	endif ()
	set(IMOGRIFY_CXX_COMPILER_GCC 1)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "IntelLLVM")
	set(IMOGRIFY_CXX_COMPILER_INTEL_LLVM 1)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	if (CMAKE_CXX_COMPILER_VERSION VERSION_LESS 19.30)
		message(WARNING "${CMAKE_PROJECT_NAME} requires MSVC 19.30 or newer.")
	endif ()
	set(IMOGRIFY_CXX_COMPILER_MSVC 1)
else()
	message(WARNING "Compiler ${CMAKE_CXX_COMPILER_VERSION} is not explicitly supported by ${CMAKE_PROJECT_NAME}.")
endif ()
