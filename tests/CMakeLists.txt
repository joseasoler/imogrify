# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify_unit_tests
	tests_main.cpp
	core/build_test.cpp
	core/markdown_test.cpp
	core/memory_block_test.cpp
)

target_link_libraries(imogrify_unit_tests PRIVATE
	doctest::doctest
	fmt::fmt
	imogrify_core
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify_unit_tests imogrify_clang_format)
endif ()


