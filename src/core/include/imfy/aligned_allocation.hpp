/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/attributes.hpp>

#include <memory>

namespace imfy
{

// See HWY_ALIGNMENT in Highway for details.
inline constexpr std::size_t memory_alignment_size = 128U;

template <typename Type>
IMFY_ALWAYS_INLINE constexpr Type* assume_aligned(Type* ptr)
{
	return std::assume_aligned<memory_alignment_size, Type>(ptr);
}

void* aligned_allocation(std::size_t size);
void aligned_deallocation(const void* aligned_pointer);

} // namespace imfy