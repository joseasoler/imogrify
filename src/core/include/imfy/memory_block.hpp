/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/allocator.hpp>
#include <imfy/concepts.hpp>

#include <cstddef>
#include <memory>
#include <new>
#include <span>
#include <type_traits>

namespace imfy
{

namespace detail
{

template <pod_type Type, standard_empty_allocator Allocator>
struct memory_block_delete final
{
	explicit memory_block_delete(std::size_t blck_size) noexcept
		: block_size{blck_size}
	{
	}
	void operator()(Type* pointer) const { Allocator{}.deallocate(pointer, block_size); }

	std::size_t block_size;
};

} // namespace detail

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

	explicit memory_block(size_type block_size)
		: block_{Allocator{}.allocate(block_size), detail::memory_block_delete<value_type, Allocator>{block_size}}
	{
	}
	memory_block() = delete;
	memory_block(const memory_block&) = delete;
	memory_block(memory_block&&) noexcept = default;
	memory_block& operator=(const memory_block&) = delete;
	memory_block& operator=(memory_block&&) noexcept = default;
	~memory_block() = default;

	[[nodiscard]] size_type size() const noexcept { return block_.get_deleter().block_size; }
	[[nodiscard]] std::span<value_type> span() noexcept { return {block_.get(), size()}; }
	[[nodiscard]] std::span<const value_type> span() const noexcept { return {block_.get(), size()}; }

private:
	std::unique_ptr<value_type, detail::memory_block_delete<value_type, Allocator>> block_;
};

} // namespace imfy