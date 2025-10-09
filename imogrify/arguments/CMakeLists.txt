# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_arguments STATIC "src/arguments_parse.cpp")

target_include_directories(imogrify_arguments PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include)

target_compile_definitions(imogrify_arguments PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_arguments PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_arguments PRIVATE fmt::fmt imogrify_core PUBLIC tl::expected)
