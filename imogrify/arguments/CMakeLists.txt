# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

add_library(imogrify_arguments STATIC "src/arguments_parse.cpp")

target_include_directories(imogrify_arguments PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include)

target_compile_definitions(imogrify_arguments PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_arguments PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(
	imogrify_arguments
	PRIVATE fmt::fmt imogrify_core imogrify_report
	PUBLIC tl::expected
)
