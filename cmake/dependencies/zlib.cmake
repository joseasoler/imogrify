# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(ZLIB REQUIRED)

add_dependency_metadata(
	NAME zlib
	VERSION "${ZLIB_VERSION_STRING}"
	DESCRIPTION "A free, lossless data-compression library."
	LICENSE_SPDX "Zlib"
)

