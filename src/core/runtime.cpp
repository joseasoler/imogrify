/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/runtime.hpp"

#include <imfy/vector.hpp>

#include <hwy/detect_targets.h>
#include <hwy/targets.h>
#include <libcpuid/libcpuid.h>
#include <tl/expected.hpp>

#include <cstdint>
#include <string_view>

namespace
{

tl::expected<cpu_raw_data_t, std::string_view> get_raw_data()
{
	cpu_raw_data_t raw_data{};
	if (cpuid_get_raw_data(&raw_data) != 0)
	{
		return tl::unexpected{cpuid_error()};
	}

	return raw_data;
}

tl::expected<cpu_id_t, std::string_view> get_cpu_id(cpu_raw_data_t raw_data)
{
	cpu_id_t cpu_id{};
	if (cpu_identify(&raw_data, &cpu_id) != 0)
	{
		return tl::unexpected{cpuid_error()};
	}

	return cpu_id;
}

imfy::vector<std::string_view> simd_target_names()
{
	// See hwy::SupportedAndGeneratedTargets.
	imfy::vector<std::string_view> result;
	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	constexpr auto highway_targets = static_cast<std::uint64_t>(HWY_TARGETS);
	for (auto targets = static_cast<std::uint64_t>(hwy::SupportedTargets()) & highway_targets; targets != 0U;
			 targets = targets & (targets - 1U))
	{
		const std::uint64_t current_target = targets & ~(targets - 1U);
		result.emplace_back(hwy::TargetName(static_cast<std::int64_t>(current_target)));
	}
	return result;
}

tl::expected<imfy::runtime::cpu_info, std::string_view> get_cpu_information(cpu_id_t cpu_id)
{
	imfy::runtime::cpu_info output_cpu_info;
	output_cpu_info.brand = static_cast<const char*>(cpu_id.brand_str);
	// Remove trailing spaces from the CPU brand string.
	auto last_index = output_cpu_info.brand.find_last_not_of(' ');
	output_cpu_info.brand.resize(last_index + 1U);

	output_cpu_info.microarchitecture = cpu_feature_level_str(cpu_id.feature_level);

	output_cpu_info.features = simd_target_names();

	return output_cpu_info;
}

}

namespace imfy::runtime
{

tl::expected<cpu_info, std::string_view> cpu_information()
{
	return get_raw_data().and_then(get_cpu_id).and_then(get_cpu_information);
}

}
