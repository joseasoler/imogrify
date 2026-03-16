# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

if(IMOGRIFY_CLANG_TIDY)
	find_program(
		IMOGRIFY_CLANG_TIDY_BINARY
		NAMES "clang-tidy"
		DOC "Clang-tidy binary"
	)

	if(IMOGRIFY_CLANG_TIDY_BINARY)
		set(IMOGRIFY_CLANG_TIDY_OPTIONS
				${IMOGRIFY_CLANG_TIDY_BINARY}
				-extra-arg=-Wno-unknown-warning-option
				-extra-arg=-Wno-ignored-optimization-argument
				-extra-arg=-Wno-unused-command-line-argument
				-extra-arg=-DIMOGRIFY_CLANG_TIDY_ANALYSIS
		)

		if(IMOGRIFY_CXX_COMPILER_MSVC)
			list(APPEND IMOGRIFY_CLANG_TIDY_OPTIONS --extra-arg=/EHsc)
		endif()

		if(CMAKE_COMPILE_WARNING_AS_ERROR)
			list(APPEND IMOGRIFY_CLANG_TIDY_OPTIONS -warnings-as-errors=*)
		endif()

		set(CMAKE_CXX_CLANG_TIDY ${IMOGRIFY_CLANG_TIDY_OPTIONS})
		if(IMOGRIFY_CMAKE_VERBOSE)
			message(STATUS "Found ${IMOGRIFY_CLANG_TIDY_BINARY}.")
		endif()
	else()
		message(FATAL_ERROR "clang-tidy binary not found.")
	endif()
endif()
