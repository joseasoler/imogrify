# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_program(
	IMOGRIFY_CLANG_FORMAT_BINARY
	NAMES "clang-format"
	DOC "Clang-format binary"
)

if(IMOGRIFY_CLANG_FORMAT_BINARY)
	set(IMOGRIFY_CLANG_FORMAT_OPTIONS ${IMOGRIFY_CLANG_FORMAT_BINARY} --dry-run)

	if(CMAKE_COMPILE_WARNING_AS_ERROR)
		list(APPEND IMOGRIFY_CLANG_FORMAT_OPTIONS -Werror)
	endif()

	file(
		GLOB_RECURSE
		IMOGRIFY_CLANG_FORMAT_FILES
		${PROJECT_SOURCE_DIR}/imogrify/*.cpp
		${PROJECT_SOURCE_DIR}/imogrify/*.hpp
		${PROJECT_SOURCE_DIR}/tests/*.cpp
		${PROJECT_SOURCE_DIR}/tests/*.hpp
	)
	list(APPEND IMOGRIFY_CLANG_FORMAT_OPTIONS ${IMOGRIFY_CLANG_FORMAT_FILES})

	set(IMOGRIFY_CLANG_FORMAT_TIMESTAMP_FILE ${CMAKE_CURRENT_BINARY_DIR}/clang_format_timestamp.txt)

	add_custom_command(
		OUTPUT ${IMOGRIFY_CLANG_FORMAT_TIMESTAMP_FILE}
		DEPENDS ${IMOGRIFY_CLANG_FORMAT_FILES}
		COMMAND ${IMOGRIFY_CLANG_FORMAT_OPTIONS}
		COMMAND ${CMAKE_COMMAND} -E touch ${IMOGRIFY_CLANG_FORMAT_TIMESTAMP_FILE}
		WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
		COMMENT "Checking code with clang-format"
	)

	# Use target as a dependency to force clang-format to run on each compilation.
	add_custom_target(imogrify_clang_format ALL DEPENDS ${IMOGRIFY_CLANG_FORMAT_TIMESTAMP_FILE})

endif()
