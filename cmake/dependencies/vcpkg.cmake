# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if(VCPKG_TARGET_TRIPLET)
	# Define vcpkg manifest features depending on CMake option status.
	if(IMOGRIFY_BUILD_UNIT_TESTS)
		list(APPEND VCPKG_MANIFEST_FEATURES "build-unit-tests")
	endif()
	if(IMOGRIFY_USE_LIBCPUID)
		list(APPEND VCPKG_MANIFEST_FEATURES "use-libcpuid")
	endif()
	if(IMOGRIFY_USE_LIBASSERT)
		list(APPEND VCPKG_MANIFEST_FEATURES "use-libassert")
	endif()

	add_dependency_metadata(
		NAME vcpkg
		VERSION "2025.9.17" # Must be updated along with build-vcpkg.yml and vcpkg.json.
		DESCRIPTION "A free and open-source C/C++ package manager."
		LICENSE_SPDX "MIT"
	)

	if(IMOGRIFY_CMAKE_VERBOSE AND VCPKG_MANIFEST_FEATURES)
		set(IMOGRIFY_VCPKG_FEATURES_REPORT "vcpkg features:")
		foreach(VCPKG_FEATURE IN LISTS VCPKG_MANIFEST_FEATURES)
			string(APPEND IMOGRIFY_VCPKG_FEATURES_REPORT "\n · ${VCPKG_FEATURE}")
		endforeach()

		message(STATUS "${IMOGRIFY_VCPKG_FEATURES_REPORT}")
	endif()

endif()
