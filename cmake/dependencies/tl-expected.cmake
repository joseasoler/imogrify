# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

find_package(tl-expected REQUIRED)

add_dependency_metadata(
	NAME "tl-expected"
	VERSION ${tl-expected_VERSION}
	DESCRIPTION "Single header implementation of std::expected with functional-style extensions."
	LICENSE_SPDX "CC0-1.0"
)
