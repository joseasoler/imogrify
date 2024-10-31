/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/runtime.hpp"

#include <doctest/doctest.h>

TEST_CASE("Gather simd target names.")
{
	CHECK(!imfy::runtime::simd_target_names().empty());
}
