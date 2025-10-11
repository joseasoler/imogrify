# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(tl-expected REQUIRED)

add_dependency_metadata(
	NAME "tl-expected"
	VERSION ${tl-expected_VERSION}
	DESCRIPTION "Single header implementation of std::expected with functional-style extensions."
	LICENSE_SPDX "CC0-1.0"
)
