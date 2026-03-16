/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
