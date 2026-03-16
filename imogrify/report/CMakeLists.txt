# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

add_library(imogrify_report STATIC src/report_level.cpp src/report_queue.cpp src/report_utility.cpp)

target_include_directories(imogrify_report PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include)

set(IMOGRIFY_REPORT_COMPILE_DEFINITIONS)
if(IMOGRIFY_SHOW_DEBUG_REPORTS)
	list(APPEND IMOGRIFY_REPORT_COMPILE_DEFINITIONS IMOGRIFY_SHOW_DEBUG_REPORTS=true)
else()
	list(APPEND IMOGRIFY_REPORT_COMPILE_DEFINITIONS IMOGRIFY_SHOW_DEBUG_REPORTS=false)
endif()

target_compile_definitions(
	imogrify_report
	PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS}
	PUBLIC ${IMOGRIFY_REPORT_COMPILE_DEFINITIONS}
)
target_compile_options(imogrify_report PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(
	imogrify_report
	PRIVATE fmt::fmt imogrify_core
	PUBLIC concurrentqueue::concurrentqueue
)
