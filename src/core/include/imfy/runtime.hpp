/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <cstdint>
#include <string_view>

namespace imfy::runtime
{

struct cpu_info final
{
	imfy::string brand;
	std::string_view microarchitecture;
	imfy::vector<std::string_view> features;
};

/**
 * Gathers all required information about the CPU. Intended for writing reports.
 * @return CPU information structure.
 */
cpu_info cpu_information();

} // namespace imfy::runtime
