# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify imogrify.cpp)

target_compile_options(imogrify PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

target_link_libraries(imogrify PRIVATE
	imogrify_core
	fmt::fmt
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify imogrify_clang_format)
endif ()

install(TARGETS imogrify RUNTIME)


