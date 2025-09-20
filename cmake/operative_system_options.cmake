# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_OS_LINUX=0
		IMOGRIFY_OS_WINDOWS=1
	)
elseif (CMAKE_SYSTEM_NAME STREQUAL "Linux")
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS
		IMOGRIFY_OS_LINUX=1
		IMOGRIFY_OS_WINDOWS=0
	)
else ()
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS
			IMOGRIFY_OS_LINUX=0
			IMOGRIFY_OS_WINDOWS=0
	)
	message(WARNING "Operative system ${CMAKE_SYSTEM_NAME} is not supported by ${CMAKE_PROJECT_NAME}.")
endif ()
