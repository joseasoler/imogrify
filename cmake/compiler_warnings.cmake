# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if(IMOGRIFY_CXX_COMPILER_CLANG OR IMOGRIFY_CXX_COMPILER_GCC)
	# Warnings present in all supported versions of GCC and Clang.
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_OPTIONS
		# Enables most warnings.
		-Wall
		# Enables an extra set of warnings.
		-Wextra
		# Enforce strict standards compliance.
		-pedantic
		# Implicit type conversions that may change a value.
		-Wconversion
		# Macros that might prevent bit-wise-identical compilations are encountered.
		-Wdate-time
		# Implicit conversions from "float" to "double".
		-Wdouble-promotion
		# Redundant semicolons after in-class function definitions.
		-Wextra-semi
		# printf/scanf/strftime/strfmon format string anomalies.
		-Wformat=2
		# Dereferencing potentially null pointers.
		-Wnull-dereference
		# Avoid C-style casts.
		-Wold-style-cast
		# Overloaded virtual function names.
		-Woverloaded-virtual
		# Implicit conversions between signed and unsigned integers.
		-Wsign-conversion
		# One variable shadows another.
		-Wshadow
		# Overriding virtual functions that are not marked with the override keyword.
		-Wsuggest-override
		# A switch statement has an index of enumerated type and lacks a case.
		-Wswitch-enum
		# An undefined identifier is evaluated in an #if directive.
		-Wundef
	)
	if(IMOGRIFY_CXX_COMPILER_GCC)
		list(
			APPEND
			IMOGRIFY_CXX_COMPILE_OPTIONS
			# Pointer casts which increase alignment.
			-Wcast-align=strict
			# A requested optimization pass is disabled.
			-Wdisabled-optimization
			# Duplicated branches in if-else statements.
			-Wduplicated-branches
			# Duplicated conditions in an if-else-if chain.
			-Wduplicated-cond
			# Logical operator always evaluating to the same result.
			-Wlogical-op
			# Multiple declarations in the same scope.
			-Wredundant-decls
			# A loop cannot be optimized.
			-Wunsafe-loop-optimizations
			# Useless casts.
			-Wuseless-cast
		)
	endif()
elseif(IMOGRIFY_CXX_COMPILER_MSVC)
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_OPTIONS
		# Specify standards conformance mode to the compiler.
		/permissive-
		# Enable level 4 warnings.
		/W4
		# Code analysis.
		/analyze
	)
endif()
