# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# This module defines a list of warnings called IMOGRIFY_CPP_WARNING_FLAGS. They can be enabled by using:
# target_compile_options(${TARGET_NAME} PRIVATE ${IMOGRIFY_CPP_WARNING_FLAGS})

include_guard(GLOBAL)

set(IMOGRIFY_CPP_WARNING_FLAGS)

if (IMOGRIFY_CLANG_ALL_WARNINGS AND CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	list(APPEND IMOGRIFY_CPP_WARNING_FLAGS
		-Weverything               # Enable every Clang warning except for the following exceptions.
		-Wno-c++98-compat          # This project is not compatible with C++98.
		-Wno-c++98-compat-pedantic # This project is not compatible with C++98.
		-Wno-c++20-compat          # This project is compatible with C++20 only.
	)
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	# Warnings present in all supported versions of GCC and Clang.
	list(APPEND IMOGRIFY_CPP_WARNING_FLAGS
		-Wall                # Enables most warnings.
		-Wextra              # Enables an extra set of warnings.
		-pedantic            # Strict compliance to the standard is not met.
		-Wconversion         # Implicit type conversions that may change a value.
		-Wdate-time          # Macros that might prevent bit-wise-identical compilations are encountered.
		-Wdouble-promotion   # Implicit conversions from "float" to "double".
		-Wextra-semi         # Redundant semicolons after in-class function definitions.
		-Wformat=2           # printf/scanf/strftime/strfmon format string anomalies.
		-Wnull-dereference   # Dereferencing a pointer may lead to erroneous or undefined behavior.
		-Wold-style-cast     # C-style cast is used in a program.
		-Woverloaded-virtual # Overloaded virtual function names.
		-Wsign-conversion    # Implicit conversions between signed and unsigned integers.
		-Wshadow             # One variable shadows another.
		-Wsuggest-override   # Overriding virtual functions that are not marked with the override keyword.
		-Wswitch-enum        # A switch statement has an index of enumerated type and lacks a case.
		-Wundef              # An undefined identifier is evaluated in an #if directive.
	)
	# Enable additional warnings depending on the compiler type and version in use.
	if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		list(APPEND IMOGRIFY_CPP_WARNING_FLAGS
			-Wcast-align=strict         # Pointer casts which increase alignment.
			-Wdisabled-optimization     # A requested optimization pass is disabled because GCC is not able to do it.
			-Wduplicated-branches       # Duplicated branches in if-else statements.
			-Wduplicated-cond           # Duplicated conditions in an if-else-if chain.
			-Wlogical-op                # A logical operator is always evaluating to true or false.
			-Wredundant-decls           # Something is declared more than once in the same scope.
			-Wunsafe-loop-optimizations # The loop cannot be optimized because the compiler cannot assume anything.
			-Wuseless-cast              # Useless casts.
		)
	endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	list(APPEND IMOGRIFY_CPP_WARNING_FLAGS
		/permissive- # Specify standards conformance mode to the compiler.
		/W4          # Enable level 4 warnings.
		/analyze     # Code analysis.
		# Warnings triggered by external headers are disabled here, as /external does not seem to work as expected.
		/wd6239      # fmt.
	)
endif ()
