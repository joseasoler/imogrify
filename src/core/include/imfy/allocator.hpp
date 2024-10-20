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
 * A single definition simplifies testing different memory allocation approaches.
 * It can also be used to trace memory allocations.
 */
template <typename Type>
using allocator = std::allocator<Type>;

} // namespace imfy