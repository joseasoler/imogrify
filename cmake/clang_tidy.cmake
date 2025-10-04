# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

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

		if(CMAKE_COMPILE_WARNING_AS_ERROR)
			list(APPEND IMOGRIFY_CLANG_TIDY_OPTIONS -warnings-as-errors=*)
		endif()

		set(CMAKE_CXX_CLANG_TIDY ${IMOGRIFY_CLANG_TIDY_OPTIONS})
	else()
		message(FATAL_ERROR "clang-tidy binary not found.")
	endif()
endif()
