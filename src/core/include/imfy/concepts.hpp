/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <type_traits>

namespace imfy
{

/**
 * A type that can be trivially copied and has a standard layout.
 * @tparam Type Type to check.
 */
template <typename Type>
concept pod_type = std::is_trivially_copyable_v<Type> && std::is_standard_layout_v<Type>;

}
