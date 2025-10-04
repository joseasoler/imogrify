# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if(IMOGRIFY_CXX_COMPILER_CLANG)
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_COMPILER_CLANG=1
		IMOGRIFY_COMPILER_GCC=0
		IMOGRIFY_COMPILER_MSVC=0
	)

elseif(IMOGRIFY_CXX_COMPILER_GCC)
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_COMPILER_CLANG=0
		IMOGRIFY_COMPILER_GCC=1
		IMOGRIFY_COMPILER_MSVC=0
	)
elseif(IMOGRIFY_CXX_COMPILER_MSVC)
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_COMPILER_CLANG=0
		IMOGRIFY_COMPILER_GCC=0
		IMOGRIFY_COMPILER_MSVC=1
		NOMINMAX
		WIN32_LEAN_AND_MEAN
	)
	# UTF-8 support is applied globally.
	add_compile_definitions(UNICODE _UNICODE)
	add_compile_options(/utf-8)
	# Enable preprocessor conformance mode.
	add_compile_options(/Zc:preprocessor)
else()
	list(
		APPEND
		IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_COMPILER_CLANG=0
		IMOGRIFY_COMPILER_GCC=0
		IMOGRIFY_COMPILER_MSVC=0
	)
endif()
