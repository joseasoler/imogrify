/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/vector.hpp>

#include <string_view>

namespace imfy::runtime
{
vector<std::string_view> simd_target_names();
}