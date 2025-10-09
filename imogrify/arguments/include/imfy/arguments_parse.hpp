/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/arguments.hpp>
#include <imfy/exit_status.hpp>

#include <tl/expected.hpp>

#include <span>
#include <string_view>

namespace imfy::arguments
{
using result_t = tl::expected<data, core::exit_status>;

[[nodiscard]] result_t parse(std::span<const char*> arguments);
}
