# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify_unit_tests
	${PROJECT_SOURCE_DIR}/imogrify_application.manifest
	src/imogrify_tests_main.cpp
	src/test_preprocessor_defines.cpp
	src/core/test_build.cpp
	src/core/test_version.cpp
	src/report/test_logger.cpp
)

target_compile_definitions(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_unit_tests PRIVATE
	Catch2::Catch2
	fmt::fmt
	imogrify_core
	imogrify_report
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify_unit_tests imogrify_clang_format)
endif ()

enable_testing()
add_test(NAME imogrify_unit_tests COMMAND $<TARGET_FILE:imogrify_unit_tests>)
