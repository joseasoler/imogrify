# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at https://mozilla.org/MPL/2.0/.

set(CMAKE_C_COMPILER "clang")
set(CMAKE_CXX_COMPILER "clang++")
set(VCPKG_C_FLAGS "-march=x86-64-v3 -mavx2")
set(VCPKG_CXX_FLAGS "${VCPKG_C_FLAGS}")
include($ENV{VCPKG_ROOT}/scripts/toolchains/linux.cmake)
