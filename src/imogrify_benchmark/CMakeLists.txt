# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

find_package(lodepng REQUIRED)
find_package(SPNG REQUIRED)

add_executable(imogrify_benchmark
	benchmark.cpp
	imogrify_benchmark.cpp
	png_encode_libpng.cpp
	png_encode_lodepng.cpp
	png_encode_spng.cpp
)

target_include_directories(imogrify_benchmark PUBLIC
	$<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include
)

target_compile_definitions(imogrify_benchmark PRIVATE ${IMOGRIFY_CXX_COMPILE_DEFINITIONS})
target_compile_options(imogrify_benchmark PRIVATE ${IMOGRIFY_CXX_COMPILE_OPTIONS})

target_link_libraries(imogrify_benchmark PRIVATE
	fmt::fmt
	lodepng
	magic_enum::magic_enum
	nanobench::nanobench
	PNG::PNG
	$<IF:$<TARGET_EXISTS:spng::spng_static>,spng::spng_static,spng::spng>
	imogrify_core
	imogrify_image
)

if (IMOGRIFY_CLANG_FORMAT_BINARY)
	add_dependencies(imogrify_benchmark imogrify_clang_format)
endif ()
