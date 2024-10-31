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
IMFY_ALWAYS_INLINE constexpr Type* assume_aligned(Type* pointer)
{
	return std::assume_aligned<memory_alignment_size, Type>(pointer);
}

void* aligned_allocation_bytes(std::size_t size);
void aligned_deallocation_bytes(const void* aligned_pointer);

template <typename Type>
Type* aligned_allocation(std::size_t size)
{
	return imfy::assume_aligned(static_cast<Type*>(imfy::aligned_allocation_bytes(sizeof(Type) * size)));
}

template <typename Type>
void aligned_deallocation(const Type* aligned_pointer)
{
	imfy::aligned_deallocation_bytes(static_cast<const void*>(aligned_pointer));
}

} // namespace imfy