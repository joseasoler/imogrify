/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/allocator.hpp>

#include <vector>

namespace imfy
{

/** std::vector with the allocator defined for imogrify. */
template <typename Type>
using vector = std::vector<Type, allocator<Type>>;

} // namespace imfy