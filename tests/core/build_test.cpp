/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/build.hpp"

#include <algorithm>
#include <catch2/catch_test_macros.hpp>
#include <string_view>

using namespace std::string_view_literals;

namespace
{

constexpr char to_lower(const char character)
{
	return character >= 'A' && character <= 'Z' ? static_cast<char>(character + 'a' - 'A') : character;
}

struct is_case_insensitive_less final
{
	constexpr bool operator()(const std::string_view lhs, const std::string_view rhs) const
	{
		return std::lexicographical_compare(
				lhs.cbegin(), lhs.cend(), rhs.cbegin(), rhs.cend(),
				[](const char left, const char right) { return to_lower(left) < to_lower(right); }
		);
	}

	constexpr bool operator()(const imfy::build::dependency_t& lhs, const imfy::build::dependency_t& rhs) const
	{
		return operator()(lhs.name, rhs.name);
	}
};

template <typename array>
[[nodiscard]] constexpr bool is_in_sorted_array(const array& arr, const std::string_view& str_view)
{
	const auto iterator = std::lower_bound(arr.cbegin(), arr.cend(), str_view);
	return iterator != std::cend(arr) && (*iterator) == str_view;
}

constexpr std::array compatible_licenses{"BSL-1.0"sv, "MIT"sv, "MPL-2.0"sv};

} // Anonymous namespace

TEST_CASE("Test data", "[core][build]")
{
	STATIC_REQUIRE(std::is_sorted(compatible_licenses.cbegin(), compatible_licenses.cend(), is_case_insensitive_less{}));
}

TEST_CASE("Project information", "[core][build]")
{
	using namespace imfy::build;

	STATIC_REQUIRE(!project.name.empty());
	STATIC_REQUIRE(!project.version.empty());
	STATIC_REQUIRE(project.license == "MPL-2.0"sv);
	STATIC_REQUIRE(is_in_sorted_array(compatible_licenses, project.license));
}

TEST_CASE("Build information", "[core][build]")
{
	using namespace imfy::build;

	STATIC_REQUIRE(!build_type.empty());
	STATIC_REQUIRE(!compiler_name.empty());
	STATIC_REQUIRE(!compiler_version.empty());
}

TEST_CASE("Dependency metadata", "[core][build]")
{
	using namespace imfy::build;

	STATIC_REQUIRE(std::size(dependencies) > 0U);
	STATIC_REQUIRE(std::is_sorted(dependencies.cbegin(), dependencies.cend(), is_case_insensitive_less{}));

	STATIC_REQUIRE(std::all_of(
			dependencies.cbegin(), dependencies.cend(), [](const dependency_t& dependency) -> bool
			{ return !dependency.name.empty() && !dependency.version.empty() && !dependency.license.empty(); }
	));

	STATIC_REQUIRE(std::all_of(
			dependencies.cbegin(), dependencies.cend(),
			[](const dependency_t& dependency) -> bool { return is_in_sorted_array(compatible_licenses, dependency.license); }
	));
}
