/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/aligned_allocation.hpp"

#include <hwy/aligned_allocator.h>

#include <cstddef>

namespace imfy
{

void* aligned_allocation_bytes(std::size_t size)
{
	return imfy::assume_aligned(hwy::AllocateAlignedBytes(size, nullptr, nullptr));
}

void aligned_deallocation_bytes(const void* aligned_pointer)
{
	hwy::FreeAlignedBytes(aligned_pointer, nullptr, nullptr);
}

} // namespace imfy