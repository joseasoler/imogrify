# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Dependency metadata.
list(SORT IMOGRIFY_DEPENDENCY_DATA_LIST CASE INSENSITIVE)
string(REPLACE ";" "" IMOGRIFY_DEPENDENCY_DATA_STRING "${IMOGRIFY_DEPENDENCY_DATA_LIST}")
# Ensure that the compiler version has exactly three fields.
string(REPLACE "." ";" IMOGRIFY_CXX_COMPILER_VERSION_LIST "${CMAKE_CXX_COMPILER_VERSION}")
list(LENGTH IMOGRIFY_CXX_COMPILER_VERSION_LIST IMOGRIFY_CXX_COMPILER_VERSION_LIST_LENGTH)
while (${IMOGRIFY_CXX_COMPILER_VERSION_LIST_LENGTH} LESS 3)
	list(APPEND IMOGRIFY_CXX_COMPILER_VERSION_LIST 0)
	list(LENGTH IMOGRIFY_CXX_COMPILER_VERSION_LIST IMOGRIFY_CXX_COMPILER_VERSION_LIST_LENGTH)
endwhile ()
list(GET IMOGRIFY_CXX_COMPILER_VERSION_LIST 0 1 2 IMOGRIFY_CXX_COMPILER_VERSION_LIST)
string(REPLACE ";" "," IMOGRIFY_CXX_COMPILER_VERSION "${IMOGRIFY_CXX_COMPILER_VERSION_LIST}")
# Ensure a non-empty build type.
set(IMOGRIFY_BUILD_TYPE ${CMAKE_BUILD_TYPE})
if (NOT IMOGRIFY_BUILD_TYPE OR IMOGRIFY_BUILD_TYPE STREQUAL "")
	set(IMOGRIFY_BUILD_TYPE "Unknown")
endif ()

configure_file(include/imfy/build.hpp.in include/imfy/build.hpp @ONLY)

set(IMOGRIFY_CORE_SOURCE_FILES
	aligned_allocation.cpp
        character_encoding.cpp
	filesystem.cpp
	markdown.cpp
)

if (IMOGRIFY_BUILD_CPU_INFORMATION)
	list(APPEND IMOGRIFY_CORE_SOURCE_FILES runtime.cpp)
else ()
	list(APPEND IMOGRIFY_CORE_SOURCE_FILES runtime_no_cpuid.cpp)
endif ()

add_library(imogrify_core STATIC ${IMOGRIFY_CORE_SOURCE_FILES})

target_include_directories(imogrify_core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/include
)

target_compile_definitions(imogrify_core PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_core PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

set(IMOGRIFY_CORE_LINK_LIBRARIES
	fmt::fmt
	hwy::hwy
	tl::expected
)

if (IMOGRIFY_BUILD_CPU_INFORMATION)
	list(APPEND IMOGRIFY_CORE_LINK_LIBRARIES cpuid::cpuid)
endif ()

target_link_libraries(imogrify_core PRIVATE ${IMOGRIFY_CORE_LINK_LIBRARIES})
