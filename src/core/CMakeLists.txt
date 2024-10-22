# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Dependency metadata.
list(SORT IMOGRIFY_DEPENDENCY_DATA_LIST CASE INSENSITIVE)
string(REPLACE ";" "" IMOGRIFY_DEPENDENCY_DATA_STRING "${IMOGRIFY_DEPENDENCY_DATA_LIST}")
string(REPLACE "." "," IMOGRIFY_CXX_COMPILER_VERSION "${CMAKE_CXX_COMPILER_VERSION}")
configure_file(include/imfy/build.hpp.in include/imfy/build.hpp @ONLY)

add_library(imogrify_core STATIC
	${CMAKE_CURRENT_BINARY_DIR}/include/imfy/build.hpp
	include/imfy/allocator.hpp
	include/imfy/markdown.hpp
	include/imfy/memory_block.hpp
	include/imfy/string.hpp
	include/imfy/vector.hpp
	markdown.cpp
)

target_include_directories(imogrify_core PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
	$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>/include
)

target_compile_definitions(imogrify_core PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_core PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_core PRIVATE
	fmt::fmt
)
