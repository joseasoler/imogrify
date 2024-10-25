# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(PNG REQUIRED)

add_dependency_metadata(
	NAME libpng
	VERSION "${PNG_VERSION_STRING}"
	DESCRIPTION "A library implementing an interface for reading and writing PNG (Portable Network Graphics) format files."
	LICENSE_SPDX "libpng-2.0"
)

