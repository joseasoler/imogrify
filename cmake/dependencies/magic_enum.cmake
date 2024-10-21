# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(magic_enum REQUIRED)

add_dependency_metadata(
	NAME "Magic Enum"
	VERSION ${magic_enum_VERSION}
	DESCRIPTION "Provides static reflection for enums."
	LICENSE_SPDX "MIT"
)

