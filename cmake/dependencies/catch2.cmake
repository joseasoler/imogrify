# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_UNIT_TESTS)
	find_package(Catch2 CONFIG REQUIRED)

	add_dependency_metadata(
		NAME "Catch2"
		VERSION ${Catch2_VERSION}
		DESCRIPTION "A modern, C++-native, test framework for unit-tests."
		LICENSE_SPDX "BSL-1.0"
		USAGE "test"
	)

endif ()


