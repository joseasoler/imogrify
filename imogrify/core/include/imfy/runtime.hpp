/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <string>
#include <string_view>

namespace imfy::core::runtime
{

inline constexpr bool available = IMOGRIFY_USE_LIBCPUID;

struct cpu_info final
{
	std::string model;
	std::string_view microarchitecture;
};

[[nodiscard]] cpu_info get_cpu_info();

}
