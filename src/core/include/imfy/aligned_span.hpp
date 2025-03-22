/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_allocation.hpp>

#include <concepts>
#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace imfy
{

/**
 * Span referencing a contiguous block of aligned memory.
 * Loosely based on std::span, lacking some of its features.
 * @tparam Type
 */
template <std::unsigned_integral Type>
class aligned_span final
{
public:
	using element_type = Type;
	using value_type = std::remove_cvref<Type>;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using pointer = Type*;
	using reference = Type&;

	aligned_span() noexcept
		: data_{nullptr}
		, size_{0}
	{
	}

	aligned_span(pointer data, const size_type size) noexcept
		: data_{data}
		, size_{size}
	{
	}

	aligned_span(const aligned_span&) = default;
	aligned_span(aligned_span&&) noexcept = default;
	aligned_span& operator=(const aligned_span&) = default;
	aligned_span& operator=(aligned_span&&) noexcept = default;
	~aligned_span() = default;

	[[nodiscard]] reference operator[](size_type index) noexcept { return *imfy::assume_aligned(data_ + index); }
	[[nodiscard]] pointer data() const noexcept { return imfy::assume_aligned(data_); }
	[[nodiscard]] size_type size() const noexcept { return size_; }
	[[nodiscard]] size_type size_bytes() const noexcept { return size_ * sizeof(element_type); }
	[[nodiscard]] bool empty() const noexcept { return size_ == 0U; }

	[[nodiscard]] aligned_span<const std::uint8_t> as_bytes() const noexcept
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		return {reinterpret_cast<const std::uint8_t*>(data_), size_ * sizeof(element_type)};
	}

	[[nodiscard]] aligned_span<std::uint8_t> as_writable_bytes() const noexcept
	{
		// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
		return {reinterpret_cast<std::uint8_t*>(data_), size_ * sizeof(element_type)};
	}

private:
	pointer data_;
	size_type size_;
};

}
