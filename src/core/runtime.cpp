/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/runtime.hpp"

#include <imfy/vector.hpp>

#include <hwy/detect_targets.h>
#include <hwy/targets.h>

#include <cstdint>
#include <string_view>

namespace imfy::runtime
{

vector<std::string_view> simd_target_names()
{
	// See hwy::SupportedAndGeneratedTargets.
	vector<std::string_view> result;
	auto targets = static_cast<std::uint64_t>(hwy::SupportedTargets()) & HWY_TARGETS;
	for (; targets != 0U; targets = targets & (targets - 1U))
	{
		const std::uint64_t current_target = targets & ~(targets - 1U);
		result.emplace_back(hwy::TargetName(static_cast<std::int64_t>(current_target)));
	}
	return result;
}

} // namespace imfy::runtime