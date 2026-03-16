# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

if(IMOGRIFY_USE_LIBASSERT)
	find_package(libassert REQUIRED)

	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBASSERT=true)
	# Assertion failure triggers debug break on the assert line.
	add_compile_definitions(LIBASSERT_BREAK_ON_FAIL)

	add_dependency_metadata(
		NAME "libassert"
		VERSION ${libassert_VERSION}
		DESCRIPTION "The most over-engineered C++ assertion library."
		LICENSE_SPDX "MIT"
	)
else()
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBASSERT=false)
endif()
