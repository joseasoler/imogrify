# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

# Platform or compiler-specific defines.
if (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
	# imogrify uses UTF-8 by default, unless forced to do otherwise by the Windows API.
	# See http://utf8everywhere.org/ for details.
	add_compile_definitions(UNICODE _UNICODE)
	add_compile_options(/utf-8)
	add_compile_definitions(NOMINMAX WIN32_LEAN_AND_MEAN)
endif ()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
	# Disable stack protection in debug builds to allow inspecting issues with the debugger.
	add_compile_options("$<$<CONFIG:DEBUG>:-fno-stack-protector>")
endif ()

