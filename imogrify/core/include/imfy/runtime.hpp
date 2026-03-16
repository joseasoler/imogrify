/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
