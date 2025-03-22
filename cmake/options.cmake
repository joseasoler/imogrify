# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

# See README.md for details.
option(IMOGRIFY_BUILD_CPU_INFORMATION "Show CPU information on benchmarks" OFF)
option(IMOGRIFY_BUILD_MICROBENCHMARKS "Build benchmarks" OFF)
option(IMOGRIFY_BUILD_UNIT_TESTS "Build unit tests" OFF)
option(IMOGRIFY_CLANG_TIDY "Analyze the project with clang-tidy" OFF)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	option(IMOGRIFY_CLANG_ALL_WARNINGS
		"Include most Clang warnings. This may trigger unexpected positives when using newer Clang versions" OFF)
endif ()

if (VCPKG_TARGET_TRIPLET)
	option(IMOGRIFY_VCPKG_USE_ZLIB_NG "Use the zlib-ng library instead of zlib." ON)
endif ()