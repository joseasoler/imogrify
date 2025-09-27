# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_executable(imogrify_app
		src/main.cpp
)

target_compile_definitions(imogrify_app PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_app PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_app
		PRIVATE
		imogrify_core
)
