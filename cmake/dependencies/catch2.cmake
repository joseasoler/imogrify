# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

if(IMOGRIFY_BUILD_UNIT_TESTS)
	enable_testing()

	find_package(Catch2 CONFIG REQUIRED)

	add_dependency_metadata(
		NAME "Catch2"
		VERSION ${Catch2_VERSION}
		DESCRIPTION "A modern, C++-native, test framework for unit-tests."
		LICENSE_SPDX "BSL-1.0"
	)

endif()
