# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

# Gathers dependency metadata to be stored in the application binary.
set(IMOGRIFY_DEPENDENCY_DATA_LIST)

# Creates a dependency metadata entry in the IMOGRIFY_DEPENDENCY_DATA_LIST list.
function(add_dependency_metadata)

	set(ONE_VALUE_ARGS
		NAME         # Dependency name.
		VERSION      # Dependency version.
		DESCRIPTION  # Dependency description.
		LICENSE_SPDX # Dependency license in SPDX.
	)
	cmake_parse_arguments(DPND "${OPTION_ARGS}" "${ONE_VALUE_ARGS}" "" ${ARGN})
	if (NOT DEFINED DPND_NAME)
		message(FATAL_ERROR "add_dependency_metadata called without a NAME.")
	elseif (NOT DEFINED DPND_VERSION)
		message(FATAL_ERROR "add_dependency_metadata(${DPND_NAME}) called without a VERSION.")
	elseif (NOT DEFINED DPND_DESCRIPTION)
		message(FATAL_ERROR "add_dependency_metadata(${DPND_NAME}) called without a DESCRIPTION.")
	elseif (NOT DEFINED DPND_LICENSE_SPDX)
		message(FATAL_ERROR "add_dependency_metadata(${DPND_NAME}) called without a LICENSE_SPDX.")
	endif ()

	# Convert version format.
	string(REPLACE "." ";" DPND_VERSION_LIST ${DPND_VERSION})
	list(LENGTH DPND_VERSION_LIST DPND_VERSION_SIZE)
	if (DPND_VERSION_SIZE EQUAL 2)
		string(APPEND DPND_VERSION ",0")
	endif ()

	string(REPLACE "." "," DPND_VERSION ${DPND_VERSION})
	set(DPND_VERSION "{${DPND_VERSION}}")

	set(DPND_METADATA "dependency_t{\"${DPND_NAME}\",${DPND_VERSION},\"${DPND_DESCRIPTION}\",\"${DPND_LICENSE_SPDX}\"},\n")

	# Append the target to the list of known dependency targets.
	list(APPEND IMOGRIFY_DEPENDENCY_DATA_LIST "${DPND_METADATA} ")
	set(IMOGRIFY_DEPENDENCY_DATA_LIST ${IMOGRIFY_DEPENDENCY_DATA_LIST} PARENT_SCOPE)

endfunction()
