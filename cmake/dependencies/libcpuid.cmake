# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_CPU_INFORMATION)

	find_package(cpuid 0.7.0 REQUIRED)

	add_dependency_metadata(
		NAME libcpuid
		VERSION ${cpuid_VERSION}
		DESCRIPTION "Provides CPU identification."
		LICENSE_SPDX "BSD-2-Clause"
		USAGE "imogrify"
	)

endif ()
