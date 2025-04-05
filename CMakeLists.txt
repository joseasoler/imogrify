# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

cmake_minimum_required(VERSION 3.25)

# CMake options used by the project.
include(cmake/options.cmake)
# Dependency metadata included in the binary.
include(cmake/dependency_data.cmake)
# vcpkg manifest features to use in the build. Ignored when vcpkg is not in use.
include(cmake/dependencies/vcpkg.cmake)

project(imogrify
	VERSION 0.1.0
	DESCRIPTION "Image conversion tool optimized for batch processing."
	HOMEPAGE_URL "https://github.com/joseasoler/imogrify"
	LANGUAGES C CXX
)

# The project uses C++20 without any non-standard compiler extensions.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Check compiler compatibility.
include(cmake/compiler_compatibility.cmake)

# Set common target compile options and definitions for imogrify targets.
set(IMOGRIFY_CXX_COMPILE_OPTIONS)
set(IMOGRIFY_CXX_COMPILE_DEFINITIONS)
include(cmake/compiler_options.cmake)
include(cmake/operative_system_options.cmake)
include(cmake/compiler_warnings.cmake)

# Tooling.
include(cmake/clang_format.cmake)
include(cmake/clang_tidy.cmake)

# Project dependencies.
include(cmake/dependencies/zlib.cmake)
# ---
include(cmake/dependencies/catch2.cmake)
include(cmake/dependencies/fmt.cmake)
include(cmake/dependencies/libcpuid.cmake)
include(cmake/dependencies/libpng.cmake)
include(cmake/dependencies/libspng.cmake)
include(cmake/dependencies/lodepng.cmake)
include(cmake/dependencies/highway.cmake)
include(cmake/dependencies/nanobench.cmake)
include(cmake/dependencies/tl-expected.cmake)

add_subdirectory(src)

if (IMOGRIFY_BUILD_UNIT_TESTS)
	add_subdirectory(tests)
	enable_testing()
	add_test(NAME imogrify_unit_tests COMMAND $<TARGET_FILE:imogrify_unit_tests>)
endif ()
