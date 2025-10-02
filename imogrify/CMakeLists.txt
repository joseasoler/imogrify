# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

# Cross-platform utilities used by other layers.
add_subdirectory(core)
# Report data back to the user.
add_subdirectory(report)
# Arguments definition and parsing.
add_subdirectory(arguments)
# Executable of the application.
add_subdirectory(app)

if (IMOGRIFY_BUILD_UNIT_TESTS)
	add_subdirectory(unit_tests)
endif ()
