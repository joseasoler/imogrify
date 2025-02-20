/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

#include <cstdint>
#include <string_view>

namespace imfy::runtime
{

struct cpu_info final
{
	string brand;
	std::string_view microarchitecture;
	vector<std::string_view> features;
};

/**
 * Gathers all required information about the CPU. Intended for writing reports.
 * @return CPU information structure or an error description.
 */
tl::expected<cpu_info, std::string_view> cpu_information();

}
