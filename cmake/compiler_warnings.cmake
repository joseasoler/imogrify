# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (IMOGRIFY_CLANG_ALL_WARNINGS AND IMOGRIFY_CXX_COMPILER_CLANG)
	list(APPEND IMOGRIFY_CXX_COMPILE_OPTIONS
		-Weverything                # Enable all warning except for:
		-Wno-c++98-compat           # C++20 project.
		-Wno-c++98-compat-pedantic  # C++20 project.
		-Wno-covered-switch-default # Prefer a explicit default label.
		-Wno-documentation          # Fails when tparam is used in concepts.
		-Wno-unsafe-buffer-usage    # Allow pointer arithmetic.
	)
elseif (IMOGRIFY_CXX_COMPILER_CLANG OR IMOGRIFY_CXX_COMPILER_GCC)
	# Warnings present in all supported versions of GCC and Clang.
	list(APPEND IMOGRIFY_CXX_COMPILE_OPTIONS
		-Wall                # Enables most warnings.
		-Wextra              # Enables an extra set of warnings.
		-pedantic            # Enforce strict standards compliance.
		-Wconversion         # Implicit type conversions that may change a value.
		-Wdate-time          # Macros that might prevent bit-wise-identical compilations are encountered.
		-Wdouble-promotion   # Implicit conversions from "float" to "double".
		-Wextra-semi         # Redundant semicolons after in-class function definitions.
		-Wformat=2           # printf/scanf/strftime/strfmon format string anomalies.
		-Wnull-dereference   # Dereferencing potentially null pointers.
		-Wold-style-cast     # Avoid C-style casts.
		-Woverloaded-virtual # Overloaded virtual function names.
		-Wsign-conversion    # Implicit conversions between signed and unsigned integers.
		-Wshadow             # One variable shadows another.
		-Wsuggest-override   # Overriding virtual functions that are not marked with the override keyword.
		-Wswitch-enum        # A switch statement has an index of enumerated type and lacks a case.
		-Wundef              # An undefined identifier is evaluated in an #if directive.
	)
	# Enable additional warnings depending on the compiler type and version in use.
	if (IMOGRIFY_CXX_COMPILER_GCC)
		list(APPEND IMOGRIFY_CXX_COMPILE_OPTIONS
			-Wcast-align=strict         # Pointer casts which increase alignment.
			-Wdisabled-optimization     # A requested optimization pass is disabled.
			-Wduplicated-branches       # Duplicated branches in if-else statements.
			-Wduplicated-cond           # Duplicated conditions in an if-else-if chain.
			-Wlogical-op                # Logical operator always evaluating to the same result.
			-Wredundant-decls           # Multiple declarations in the same scope.
			-Wunsafe-loop-optimizations # A loop cannot be optimized.
			-Wuseless-cast              # Useless casts.
		)
	endif ()
elseif (IMOGRIFY_CXX_COMPILER_MSVC)
	list(APPEND IMOGRIFY_CXX_COMPILE_OPTIONS
		/permissive- # Specify standards conformance mode to the compiler.
		/W4          # Enable level 4 warnings.
		/analyze     # Code analysis.
		# Warnings triggered by external headers.
		/wd6239      # fmt.
	)
endif ()
