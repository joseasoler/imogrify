# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_MICROBENCHMARKS)
	find_package(SPNG REQUIRED)

	add_dependency_metadata(
		NAME libspng
		VERSION ${SPNG_VERSION}
		DESCRIPTION "C library for reading and writing Portable Network Graphics (PNG) format files with a focus on security and ease of use."
		LICENSE_SPDX "BSD-2-Clause"
		USAGE "benchmark"
	)

endif ()
