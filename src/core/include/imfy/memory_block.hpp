/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_allocation.hpp>
#include <imfy/aligned_span.hpp>
#include <imfy/attributes.hpp>
#include <imfy/concepts.hpp>

#include <cstddef>
#include <cstring>
#include <memory>
#include <type_traits>

namespace imfy
{

/**
 * Memory block with managed allocation and de-allocation.
 * Data is uninitialized by default.
 * @tparam Type Standard layout type stored by the memory block.
 */
template <pod_type Type>
class memory_block final
{
public:
	using value_type = Type;
	using size_type = std::size_t;

	explicit memory_block(const size_type block_size)
	{
		IMFY_ASSUME(block_size > 0);
		// NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
		block_ = aligned_allocation<value_type>(block_size);
		// NOLINTNEXTLINE(cppcoreguidelines-prefer-member-initializer)
		size_ = block_size;
	}

	memory_block() = delete;
	memory_block(const memory_block&) = delete;
	memory_block(memory_block&& other) noexcept
		: block_{other.block_}
		, size_{other.size_}
	{
		other.block_ = nullptr;
		other.size_ = 0U;
	}
	memory_block& operator=(const memory_block&) = delete;
	memory_block& operator=(memory_block&& rhs) noexcept
	{
		block_ = rhs.block_;
		size_ = rhs.size_;
		rhs.block_ = nullptr;
		rhs.size_ = 0U;
		return *this;
	}
	~memory_block() { aligned_deallocation(block_); }

	[[nodiscard]] size_type size() const noexcept { return size_; }
	[[nodiscard]] aligned_span<value_type> span() noexcept { return {block_, size()}; }
	[[nodiscard]] aligned_span<const value_type> span() const noexcept { return {block_, size()}; }

	void enlarge(size_type block_size)
	{
		memory_block new_block(block_size);
		const value_type* IMFY_RESTRICT current_pointer = block_;
		value_type* IMFY_RESTRICT new_pointer = new_block.block_;
		std::memcpy(new_pointer, current_pointer, size_);
		std::swap(new_block, *this);
	}

private:
	value_type* block_;
	size_type size_;
};

}
