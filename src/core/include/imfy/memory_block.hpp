/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstddef>
#include <cstdlib>
#include <new>
#include <span>
#include <type_traits>

namespace imfy
{

template <typename Type>
concept trivial_standard_layout = std::is_trivial_v<Type> && std::is_standard_layout_v<Type>;

/**
 * Memory block with managed allocation and de-allocation.
 * Data is uninitialized by default.
 * Aborts on memory allocation failures.
 * @tparam Type Standard layout type stored by the memory block.
 */
template <typename Type>
	requires trivial_standard_layout<Type>
class memory_block final
{
public:
	using value_type = Type;
	using size_type = std::size_t;

	explicit memory_block(size_type size) noexcept
		: block_{static_cast<value_type*>(::operator new(sizeof(value_type) * size, std::nothrow))}
		, size_{size}
	{
		if (block_ == nullptr) [[unlikely]]
		{
			std::abort();
		}
	}
	memory_block() = delete;
	memory_block(const memory_block&) = delete;
	memory_block(memory_block&&) noexcept = default;
	memory_block& operator=(const memory_block&) = delete;
	memory_block& operator=(memory_block&&) noexcept = default;

	~memory_block() { ::operator delete(block_, std::nothrow); }

	[[nodiscard]] const value_type* data() const noexcept { return block_; }
	[[nodiscard]] size_type size() const noexcept { return size_; }
	[[nodiscard]] std::span<value_type> span() noexcept { return {block_, size_}; }

private:
	value_type* block_;
	size_type size_;
};

} // namespace imfy