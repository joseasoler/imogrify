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

/**
 * Promises that the memory addressed by pointer is aligned to at least memory_alignment_size.
 * @tparam Type Type of the parameter pointer.
 * @param pointer Aligned pointer.
 * @return Aligned pointer.
 */
template <typename Type>
IMFY_ALWAYS_INLINE constexpr Type* assume_aligned(Type* pointer)
{
	return std::assume_aligned<memory_alignment_size, Type>(pointer);
}

/**
 * Allocates a contiguous aligned memory chunk of the requested size.
 * @param size Size of the block. Must be more than zero and less than std::numeric_limits<size_t>::max() / 2.
 * @return Pointer to the newly allocated memory.
 */
void* aligned_allocation_bytes(std::size_t size);

/**
 * Deallocates a memory chunk allocated by aligned_allocation_bytes.
 * @param aligned_pointer Memory to deallocate. Must have been allocated by aligned_allocation_bytes.
 */
void aligned_deallocation_bytes(const void* aligned_pointer);

/**
 * Allocates a contiguous memory array of elements of a specific type.
 * @tparam Type Type of the elements.
 * @param size Size of the block. size * sizeof(Type) must be less than std::numeric_limits<size_t>::max() / 2.
 * @return Pointer to the newly allocated memory.
 */
template <typename Type>
Type* aligned_allocation(std::size_t size)
{
	return imfy::assume_aligned(static_cast<Type*>(imfy::aligned_allocation_bytes(sizeof(Type) * size)));
}

/**
 * Deallocates a memory array allocated by aligned_allocation_bytes.
 * @tparam Type Type of the elements.
*  @param aligned_pointer Memory to deallocate. Must have been allocated by aligned_allocation.
 */
template <typename Type>
void aligned_deallocation(const Type* aligned_pointer)
{
	imfy::aligned_deallocation_bytes(static_cast<const void*>(aligned_pointer));
}

} // namespace imfy