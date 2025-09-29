# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_USE_LIBCPUID)
	find_package(cpuid REQUIRED)

	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBCPUID=1)

	add_dependency_metadata(
		NAME libcpuid
		VERSION ${cpuid_VERSION}
		DESCRIPTION "Provides CPU identification."
		LICENSE_SPDX "BSD-2-Clause"
	)
else ()
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBCPUID=0)
endif ()


