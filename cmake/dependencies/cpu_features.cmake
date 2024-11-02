# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)


find_package(CpuFeatures REQUIRED)

add_dependency_metadata(
	NAME cpu_features
	VERSION ${CpuFeatures_VERSION}
	DESCRIPTION "A cross-platform C library to retrieve CPU features at runtime."
	LICENSE_SPDX "Apache-2.0"
	USAGE "imogrify"
)

