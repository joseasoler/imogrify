/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_allocation.hpp>
#include <imfy/aligned_span.hpp>
#include <imfy/concepts.hpp>

#include <cstddef>
#include <memory>
#include <new>
#include <type_traits>

namespace imfy
{

/**
 * Memory block with managed allocation and de-allocation.
 * Data is uninitialized by default.
 * Aborts on memory allocation failures.
 * @tparam Type Standard layout type stored by the memory block.
 */
template <pod_type Type>
class memory_block final
{
public:
	using value_type = Type;
	using size_type = std::size_t;

	explicit memory_block(size_type block_size)
		: block_{aligned_allocation<value_type>(block_size)}
		, size_{block_size}
	{
	}
	memory_block() = delete;
	memory_block(const memory_block&) = delete;
	memory_block(memory_block&&) noexcept = default;
	memory_block& operator=(const memory_block&) = delete;
	memory_block& operator=(memory_block&&) noexcept = default;
	~memory_block() { aligned_deallocation(block_); }

	[[nodiscard]] size_type size() const noexcept { return size_; }
	[[nodiscard]] aligned_span<value_type> span() noexcept { return {block_, size()}; }
	[[nodiscard]] aligned_span<const value_type> span() const noexcept { return {block_, size()}; }

private:
	value_type* block_;
	size_type size_;
};

} // namespace imfy