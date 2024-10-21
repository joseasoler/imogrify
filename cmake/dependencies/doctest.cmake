# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_UNIT_TESTS)
	find_package(doctest REQUIRED)

	add_dependency_metadata(
		NAME doctest
		VERSION ${doctest_VERSION}
		DESCRIPTION "Fast C++ testing framework."
		LICENSE_SPDX "MIT"
	)

endif ()


