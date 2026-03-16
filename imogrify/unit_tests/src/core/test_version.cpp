/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <imfy/version.hpp>

#include <cstdint>
#include <type_traits>

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Type traits")
{
	using imfy::core::build::version_t;
	STATIC_REQUIRE(sizeof(version_t) < sizeof(std::uint64_t));
	STATIC_REQUIRE(std::is_trivially_copyable_v<version_t> && std::is_standard_layout_v<version_t>);

	STATIC_REQUIRE(version_t{}.major == 0U);
	STATIC_REQUIRE(version_t{}.minor == 0U);
	STATIC_REQUIRE(version_t{}.patch == 0U);
}
