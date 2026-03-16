# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

add_executable(imogrify ${PROJECT_SOURCE_DIR}/imogrify_application.manifest src/main.cpp)

target_compile_definitions(imogrify PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify PRIVATE fmt::fmt tl::expected imogrify_core imogrify_report imogrify_arguments)

if (IMOGRIFY_CLANG_FORMAT)
	add_dependencies(imogrify imogrify_clang_format)
endif ()