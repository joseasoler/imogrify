add_library(enchantum INTERFACE include/enchantum_single_header.hpp)

target_include_directories(enchantum SYSTEM INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}>/include)

add_library(enchantum::enchantum ALIAS enchantum)
