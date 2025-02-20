/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <memory>

namespace imfy
{

/**
 * Conformant allocator to use with C++ Standard Library types in imogrify.
 * A singular definition point allows testing different memory allocation implementation or to trace them.
 */
template <typename Type>
using allocator = std::allocator<Type>;

}
