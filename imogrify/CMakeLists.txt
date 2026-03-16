# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

# Cross-platform utilities used by other layers.
add_subdirectory(core)
# Report data back to the user.
add_subdirectory(report)
# Arguments definition and parsing.
add_subdirectory(arguments)
# Executable of the application.
add_subdirectory(app)

if(IMOGRIFY_BUILD_UNIT_TESTS)
	add_subdirectory(unit_tests)
endif()
