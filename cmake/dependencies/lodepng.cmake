# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_BUILD_MICROBENCHMARKS)
	find_package(lodepng REQUIRED)

	add_dependency_metadata(
		NAME lodepng
		VERSION "2021.12.4"
		DESCRIPTION "PNG image decoder and encoder, all in one, no dependency or linkage to zlib or libpng required."
		LICENSE_SPDX "Zlib"
		USAGE "benchmark"
	)

endif ()


