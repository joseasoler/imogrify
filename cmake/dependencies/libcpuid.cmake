# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

if(IMOGRIFY_USE_LIBCPUID)
	find_package(cpuid REQUIRED)

	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBCPUID=true)

	add_dependency_metadata(
		NAME libcpuid
		VERSION ${cpuid_VERSION}
		DESCRIPTION "Provides CPU identification."
		LICENSE_SPDX "BSD-2-Clause"
	)
else()
	list(APPEND IMOGRIFY_CXX_COMPILE_DEFINITIONS IMOGRIFY_USE_LIBCPUID=false)
endif()
