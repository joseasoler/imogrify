# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify_unit_tests
	tests_main.cpp
	preprocessor_definitions_test.cpp
	core/build_test.cpp
	core/concepts_test.cpp
	core/memory_block_test.cpp
	image/image_size_test.cpp
	image/png_format_test.cpp
	image/raw_image_test.cpp
	# https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page
	imogrify_unit_tests.manifest
)

target_compile_definitions(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_unit_tests PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_unit_tests PRIVATE
	doctest::doctest
	fmt::fmt
	PNG::PNG
	ZLIB::ZLIB
	imogrify_core
	imogrify_image
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify_unit_tests imogrify_clang_format)
endif ()


