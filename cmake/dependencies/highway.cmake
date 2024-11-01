# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(hwy REQUIRED)

add_dependency_metadata(
	NAME "Highway"
	VERSION ${hwy_VERSION}
	DESCRIPTION "Performance-portable, length-agnostic SIMD with runtime dispatch."
	LICENSE_SPDX "Apache-2.0"
	USAGE "imogrify"
)

