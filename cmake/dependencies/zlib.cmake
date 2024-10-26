# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(ZLIB REQUIRED)

if (VCPKG_TARGET_TRIPLET)
	# vcpkg uses zlib-ng compiled with -DZLIB_COMPAT=on by default.
	# zlib-ng exposes a zlib compatible API, and a valid zlib header version.
	# For metadata we are interested on the real zlib-ng version, which only seems to be exposed through the
	# ZLIBNG_VERSION define in zlib.h.
	get_target_property(ZLIB_INCLUDE_DIRECTORY ZLIB::ZLIB INTERFACE_INCLUDE_DIRECTORIES)
	file(READ "${ZLIB_INCLUDE_DIRECTORY}/zlib.h" ZLIB_HEADER_FILE)
	string(REGEX MATCH "ZLIBNG_VERSION \"([0-9]+)\.([0-9]+)\.([0-9]+)" ZLIB_NG_VERSION "${ZLIB_HEADER_FILE}")
	string(SUBSTRING "${ZLIB_NG_VERSION}" 16 -1 ZLIB_NG_VERSION)
	add_dependency_metadata(
		NAME zlib-ng
		VERSION "${ZLIB_NG_VERSION}"
		DESCRIPTION "A zlib data compression library for the next generation systems."
		LICENSE_SPDX "Zlib"
	)
else ()
	add_dependency_metadata(
		NAME zlib
		VERSION "${ZLIB_VERSION_STRING}"
		DESCRIPTION "A free, lossless data-compression library."
		LICENSE_SPDX "Zlib"
	)
endif ()

