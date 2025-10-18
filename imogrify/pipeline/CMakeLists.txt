# This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
# distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.

add_library(imogrify_pipeline STATIC src/log_queue.cpp src/pipeline.cpp)

target_include_directories(imogrify_pipeline PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include)

target_compile_definitions(imogrify_pipeline PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_pipeline PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(
	imogrify_pipeline
	PRIVATE enchantum::enchantum fmt::fmt imogrify_core imogrify_report
	PUBLIC concurrentqueue::concurrentqueue
)
