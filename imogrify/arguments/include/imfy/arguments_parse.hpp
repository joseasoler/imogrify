/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <imfy/arguments.hpp>
#include <imfy/exit_status.hpp>

#include <tl/expected.hpp>

#include <span>
#include <string_view>

namespace imfy::arguments
{
using result_t = tl::expected<arg_data, core::exit_status>;

[[nodiscard]] result_t parse(std::span<const char*> arguments);
}
