/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/allocator.hpp>
#include <imfy/concepts.hpp>

#include <cstddef>
#include <new>
#include <span>
#include <type_traits>

namespace imfy
{

/**
 * Memory block with managed allocation and de-allocation.
 * Data is uninitialized by default.
 * Aborts on memory allocation failures.
 * @tparam Type Standard layout type stored by the memory block.
 */
template <pod_type Type, standard_empty_allocator Allocator = imfy::allocator<Type>>
class memory_block final
{
public:
	using value_type = Type;
	using size_type = typename Allocator::size_type;

	explicit memory_block(size_type size)
		: block_{Allocator{}.allocate(size)}
		, size_{size}
	{
	}
	memory_block() = delete;
	memory_block(const memory_block&) = delete;
	memory_block(memory_block&&) noexcept = default;
	memory_block& operator=(const memory_block&) = delete;
	memory_block& operator=(memory_block&&) noexcept = default;

	~memory_block() { Allocator{}.deallocate(block_, size_); }

	[[nodiscard]] size_type size() const noexcept { return size_; }
	[[nodiscard]] std::span<value_type> span() noexcept { return {block_, size_}; }

private:
	value_type* block_;
	size_type size_;
};

} // namespace imfy