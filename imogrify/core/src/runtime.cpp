/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/runtime.hpp"

#include <libcpuid/libcpuid.h>

namespace imfy::core::runtime
{

cpu_info get_cpu_info()
{
	if constexpr (!available)
	{
		return {.model{}, .microarchitecture = "Runtime CPU information not available."};
	}

	if (cpuid_present() == 0)
	{
		return {.model{}, .microarchitecture = "CPU information not available."};
	}
	cpu_raw_data_t raw_data{};
	cpu_id_t cpu_id{};
	if (cpuid_get_raw_data(&raw_data) != 0 || cpu_identify(&raw_data, &cpu_id) != 0)
	{
		return {.model{}, .microarchitecture = cpuid_error()};
	}

	cpu_info info{};
	info.model = static_cast<const char*>(cpu_id.brand_str);
	// Remove trailing spaces from the CPU brand string.
	auto last_index = info.model.find_last_not_of(' ');
	info.model.resize(last_index + 1U);

	info.microarchitecture = cpu_feature_level_str(cpu_id.feature_level);
	return info;
}

}
