# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

add_executable(imogrify_unit_tests
	${PROJECT_SOURCE_DIR}/imogrify_application.manifest
	src/imogrify_tests_main.cpp
	src/test_preprocessor_defines.cpp
	src/core/test_build.cpp
	src/core/test_version.cpp
	src/report/test_report_queue.cpp
	src/arguments/test_arguments_definition.cpp
)

target_compile_definitions(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_unit_tests PRIVATE
	Catch2::Catch2
	fmt::fmt
	imogrify_core
	imogrify_report
	imogrify_arguments
)

if (IMOGRIFY_CLANG_FORMAT)
	add_dependencies(imogrify_unit_tests imogrify_clang_format)
endif ()

include(Catch)
set(CMAKE_CATCH_DISCOVER_TESTS_DISCOVERY_MODE PRE_TEST)
catch_discover_tests(imogrify_unit_tests)
