# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_subdirectory(core)
add_subdirectory(image)
add_subdirectory(imogrify)

if (IMOGRIFY_BUILD_MICROBENCHMARKS)
	add_subdirectory(imogrify_benchmark)
endif ()
