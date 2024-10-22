# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify
	imogrify.cpp
	# https://learn.microsoft.com/en-us/windows/apps/design/globalizing/use-utf8-code-page
	imogrify.manifest
)

target_compile_definitions(imogrify PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify PRIVATE
	imogrify_core
	fmt::fmt
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify imogrify_clang_format)
endif ()

install(TARGETS imogrify RUNTIME)


