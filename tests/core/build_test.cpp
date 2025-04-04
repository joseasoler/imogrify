/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/build.hpp"

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

struct is_case_insensitive_less final
{
	constexpr bool operator()(const std::string_view lhs, const std::string_view rhs) const
	{
		return std::ranges::lexicographical_compare(
				lhs, rhs, [](const char lhs_char, const char rhs_char) { return to_lower(lhs_char) < to_lower(rhs_char); }
		);
	}

	constexpr bool operator()(const imfy::build::dependency_t& lhs, const imfy::build::dependency_t& rhs) const
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

constexpr std::array compatible_licenses{"Apache-2.0"sv, "BSD-2-Clause"sv, "BSL-1.0"sv, "CC0-1.0"sv,
																				 "libpng-2.0"sv, "MIT"sv,					 "MPL-2.0"sv, "Zlib"sv};

}

TEST_CASE("Test data")
{
	static_assert(std::ranges::is_sorted(compatible_licenses, is_case_insensitive_less{}));
}

TEST_CASE("Project information")
{
	using namespace imfy::build;

	static_assert(!project.name.empty());
	static_assert(project.version.major > 0U || project.version.minor > 0U || project.version.patch > 0U);
	static_assert(project.license == "MPL-2.0"sv);
	static_assert(is_in_array(compatible_licenses, project.license));
	static_assert(!build_type.empty());
}

TEST_CASE("Compiler information")
{
	using namespace imfy::build;
	static_assert(!compiler_name().empty(), "Unsupported compiler. Please update the compiler metadata information.");
	static_assert(compiler_version.major > 0U || compiler_version.minor > 0U || compiler_version.patch > 0U);
}

TEST_CASE("Dependency metadata")
{
	using namespace imfy::build;

	static_assert(std::size(dependencies) > 0U);
	static_assert(std::ranges::is_sorted(dependencies, is_case_insensitive_less{}));

	static_assert(std::ranges::all_of(
			dependencies, [](const dependency_t& dependency) -> bool
			{ return !dependency.name.empty() && !dependency.description.empty() && !dependency.license.empty(); }
	));

	static_assert(std::ranges::all_of(
			dependencies, [](const dependency_t& dependency) -> bool
			{ return dependency.version.major != 0U || dependency.version.minor != 0U || dependency.version.patch != 0U; }
	));

	static_assert(std::ranges::all_of(
			dependencies,
			[](const dependency_t& dependency) -> bool { return is_in_array(compatible_licenses, dependency.license); }
	));
}
