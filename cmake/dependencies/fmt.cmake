# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(fmt REQUIRED)

add_dependency_metadata(
	NAME fmt
	VERSION ${fmt_VERSION}
	DESCRIPTION "An open-source formatting library."
	LICENSE_SPDX "MIT"
	USAGE "imogrify"
)
if (${fmt_VERSION} GREATER_EQUAL 11.0.0)
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_USE_FMT_BASE_HEADER=1
	)
else ()
	# Older versions of fmt lack the fmt/base.h header.
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_USE_FMT_BASE_HEADER=0
	)
endif ()
