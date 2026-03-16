# SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
# SPDX-License-Identifier: AGPL-3.0-or-later

include_guard(GLOBAL)

find_package(concurrentqueue CONFIG REQUIRED)

add_dependency_metadata(
	NAME ConcurrentQueue
	VERSION ${concurrentqueue_VERSION}
	DESCRIPTION "An industrial-strength lock-free queue for C++."
	LICENSE_SPDX "BSD-2-Clause"
)
