/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/build.hpp>

#include <algorithm>
#include <array>
#include <string_view>

#include <catch2/catch_test_macros.hpp>

using namespace std::string_view_literals;

namespace
{

char to_lower(const char character)
{
	return character >= 'A' && character <= 'Z' ? static_cast<char>(character + 'a' - 'A') : character;
}

using imfy::core::build::dependency_t;

struct is_case_insensitive_less final
{
	bool operator()(const std::string_view lhs, const std::string_view rhs) const
	{
		return std::ranges::lexicographical_compare(
				lhs, rhs, [](const char lhs_char, const char rhs_char) { return to_lower(lhs_char) < to_lower(rhs_char); }
		);
	}

	bool operator()(const dependency_t& lhs, const dependency_t& rhs) const { return operator()(lhs.name, rhs.name); }
};

template <typename array>
[[nodiscard]] bool is_in_array(const array& arr, const std::string_view& str_view)
{
	const auto iterator = std::find(arr.cbegin(), arr.cend(), str_view);
	return iterator != std::cend(arr) && (*iterator) == str_view;
}

constexpr std::array compatible_licenses_spdx{"Apache-2.0"sv, "BSD-2-Clause"sv, "BSD-3-Clause"sv,
																							"BSL-1.0"sv,		"CC0-1.0"sv,			"libpng-2.0"sv,
																							"MIT"sv,				"MPL-2.0"sv,			"Zlib"sv};

[[nodiscard]] bool valid_dependency_text(const dependency_t& dependency)
{
	return !dependency.name.empty() && !dependency.description.empty() && !dependency.license.empty();
}

[[nodiscard]] bool valid_dependency_version(const dependency_t& dependency)
{
	return dependency.version.major != 0U || dependency.version.minor != 0U || dependency.version.patch != 0U;
}

[[nodiscard]] bool compatible_dependency_license(const dependency_t& dependency)
{
	return is_in_array(compatible_licenses_spdx, dependency.license);
}

}

TEST_CASE("Test data")
{
	REQUIRE(std::ranges::is_sorted(compatible_licenses_spdx, is_case_insensitive_less{}));
}

TEST_CASE("Project information")
{
	using namespace imfy::core::build;

	STATIC_REQUIRE(!project.name.empty());
	STATIC_REQUIRE(project.version.major > 0U || project.version.minor > 0U || project.version.patch > 0U);
	STATIC_REQUIRE(project.license == "MPL-2.0"sv);
	REQUIRE(is_in_array(compatible_licenses_spdx, project.license));
	STATIC_REQUIRE(!build_type.empty());
}

TEST_CASE("Compiler information")
{
	using namespace imfy::core::build;
	STATIC_REQUIRE(!compiler_name().empty());
	static_assert(compiler_version.major > 0U || compiler_version.minor > 0U || compiler_version.patch > 0U);
}

TEST_CASE("Dependency metadata")
{
	using namespace imfy::core::build;

	STATIC_REQUIRE(std::size(dependencies) > 0U);
	REQUIRE(std::ranges::is_sorted(dependencies, is_case_insensitive_less{}));
	REQUIRE(std::ranges::all_of(dependencies, valid_dependency_text));
	REQUIRE(std::ranges::all_of(dependencies, valid_dependency_version));
	REQUIRE(std::ranges::all_of(dependencies, compatible_dependency_license));
}
