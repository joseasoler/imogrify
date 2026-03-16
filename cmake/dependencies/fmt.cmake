# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

find_package(fmt REQUIRED)

add_dependency_metadata(
	NAME fmt
	VERSION ${fmt_VERSION}
	DESCRIPTION "An open-source formatting library."
	LICENSE_SPDX "MIT"
)
