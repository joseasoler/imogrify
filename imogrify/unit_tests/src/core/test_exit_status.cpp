/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/exit_status.hpp>

#include <cstdlib>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("exit_status")
{
	using imfy::core::exit_status;
	STATIC_REQUIRE(static_cast<int>(exit_status::success) == EXIT_SUCCESS);
	STATIC_REQUIRE(static_cast<int>(exit_status::unknown_error) == EXIT_FAILURE);
}
