/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#include <imfy/build.hpp>

#include <algorithm>
#include <array>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace
{

constexpr char to_lower(const char character)
{
	return character >= 'A' && character <= 'Z' ? static_cast<char>(character + 'a' - 'A') : character;
}

using imfy::core::build::dependency_t;

struct is_case_insensitive_less final
{
	constexpr bool operator()(const std::string_view lhs, const std::string_view rhs) const
	{
		return std::ranges::lexicographical_compare(
				lhs, rhs, [](const char lhs_char, const char rhs_char) { return to_lower(lhs_char) < to_lower(rhs_char); }
		);
	}

	constexpr bool operator()(const dependency_t& lhs, const dependency_t& rhs) const
	{
		return operator()(lhs.name, rhs.name);
	}
};

template <typename array>
[[nodiscard]] constexpr bool is_in_array(const array& arr, const std::string_view& str_view)
{
	const auto iterator = std::find(arr.cbegin(), arr.cend(), str_view);
	return iterator != std::cend(arr) && (*iterator) == str_view;
}

constexpr auto agpl_license_spdx = "AGPL-3.0-or-later"sv;

constexpr std::array compatible_licenses_spdx{agpl_license_spdx, "Apache-2.0"sv, "BSD-2-Clause"sv, "BSD-3-Clause"sv,
																							"BSL-1.0"sv,			 "CC0-1.0"sv,		 "libpng-2.0"sv,	 "MIT"sv,
																							"MPL-2.0"sv,			 "Zlib"sv};

[[nodiscard]] constexpr bool valid_dependency_text(const dependency_t& dependency)
{
	return !dependency.name.empty() && !dependency.description.empty() && !dependency.license.empty();
}

[[nodiscard]] constexpr bool valid_dependency_version(const dependency_t& dependency)
{
	return dependency.version.major != 0U || dependency.version.minor != 0U || dependency.version.patch != 0U;
}

[[nodiscard]] constexpr bool compatible_dependency_license(const dependency_t& dependency)
{
	return is_in_array(compatible_licenses_spdx, dependency.license);
}

}

TEST_CASE("Test data")
{
	STATIC_REQUIRE(std::ranges::is_sorted(compatible_licenses_spdx, is_case_insensitive_less{}));
}

TEST_CASE("Project information")
{
	using namespace imfy::core::build;

	STATIC_REQUIRE(!project.name.empty());
	STATIC_REQUIRE(project.version.major > 0U || project.version.minor > 0U || project.version.patch > 0U);
	STATIC_REQUIRE(project.license == agpl_license_spdx);
	STATIC_REQUIRE(is_in_array(compatible_licenses_spdx, project.license));
	STATIC_REQUIRE(!build_type.empty());
	STATIC_REQUIRE(!project_homepage_url.empty());
}

TEST_CASE("Compiler information")
{
	using namespace imfy::core::build;
	STATIC_REQUIRE(!compiler_name().empty());
	STATIC_REQUIRE(compiler_version.major > 0U || compiler_version.minor > 0U || compiler_version.patch > 0U);
}

TEST_CASE("Dependency metadata")
{
	using namespace imfy::core::build;

	STATIC_REQUIRE(std::size(dependencies) > 0U);
	STATIC_REQUIRE(std::ranges::is_sorted(dependencies, is_case_insensitive_less{}));
	STATIC_REQUIRE(std::ranges::all_of(dependencies, valid_dependency_text));
	STATIC_REQUIRE(std::ranges::all_of(dependencies, valid_dependency_version));
	STATIC_REQUIRE(std::ranges::all_of(dependencies, compatible_dependency_license));
}
