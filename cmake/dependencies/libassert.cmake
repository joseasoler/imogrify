# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_USE_LIBASSERT)
	find_package(libassert REQUIRED)

	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBASSERT=1)

	add_dependency_metadata(
		NAME "libassert"
		VERSION ${libassert_VERSION}
		DESCRIPTION "The most over-engineered C++ assertion library."
		LICENSE_SPDX "MIT"
	)
else ()
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBASSERT=0)
endif ()


