# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (VCPKG_TARGET_TRIPLET)
	# Define vcpkg manifest features depending on CMake option status.
	if (IMOGRIFY_BUILD_CPU_INFORMATION)
		list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-cpu-information")
	endif ()
	if (IMOGRIFY_BUILD_MICROBENCHMARKS)
		list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-benchmark")
		if (IMOGRIFY_VCPKG_USE_ZLIB_NG)
			list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-benchmark-use-zlib-ng")
		else ()
			list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-benchmark-use-zlib")
		endif ()
	endif ()
	if (IMOGRIFY_BUILD_UNIT_TESTS)
		list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-tests")
	endif ()

	if (IMOGRIFY_VCPKG_USE_ZLIB_NG)
		list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-use-zlib-ng")
	else ()
		list(APPEND VCPKG_MANIFEST_FEATURES "imogrify-use-zlib")
	endif ()

	add_dependency_metadata(
		NAME vcpkg
		VERSION "2025.02.14" # Must be updated along with .github/workflows/build-vcpkg.yml and vcpkg.json.
		DESCRIPTION "A free and open-source C/C++ package manager."
		LICENSE_SPDX "MIT"
		USAGE "imogrify"
	)

endif ()