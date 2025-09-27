# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

include_guard(GLOBAL)

find_package(concurrentqueue CONFIG REQUIRED)

add_dependency_metadata(
	NAME ConcurrentQueue
	VERSION ${concurrentqueue_VERSION}
	DESCRIPTION "An industrial-strength lock-free queue for C++."
	LICENSE_SPDX "BSD-2-Clause"
)
