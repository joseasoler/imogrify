# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_report STATIC
		src/report_queue.cpp
		src/report_utility.cpp
)

target_include_directories(imogrify_report PUBLIC
		$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)

set(IMOGRIFY_REPORT_COMPILE_DEFINITIONS)
if (IMOGRIFY_SHOW_DEBUG_REPORTS)
	list(APPEND IMOGRIFY_REPORT_COMPILE_DEFINITIONS IMOGRIFY_SHOW_DEBUG_REPORTS=1)
else ()
	list(APPEND IMOGRIFY_REPORT_COMPILE_DEFINITIONS IMOGRIFY_SHOW_DEBUG_REPORTS=0)
endif ()

target_compile_definitions(imogrify_report PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS} PUBLIC ${IMOGRIFY_REPORT_COMPILE_DEFINITIONS})
target_compile_options(imogrify_report PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_report
		PRIVATE
		fmt::fmt
		imogrify_core
		PUBLIC
		concurrentqueue::concurrentqueue
)
