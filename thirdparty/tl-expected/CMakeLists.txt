add_library(expected INTERFACE)

target_include_directories(expected INTERFACE
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)
add_library(tl::expected ALIAS expected)

add_dependency_metadata(
	NAME "tl-expected"
	VERSION 1.1.0
	DESCRIPTION "Single header implementation of std::expected with functional-style extensions."
	LICENSE_SPDX "CC0-1.0"
	USAGE "imogrify"
)
