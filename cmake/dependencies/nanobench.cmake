# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_MICROBENCHMARKS)
	find_package(nanobench REQUIRED)

	add_dependency_metadata(
		NAME nanobench
		VERSION 4.3.11
		DESCRIPTION "A platform independent microbenchmarking library for C++."
		LICENSE_SPDX "MIT"
		USAGE "benchmark"
	)

endif ()
