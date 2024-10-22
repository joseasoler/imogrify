/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <type_traits>

namespace imfy
{

/**
 * A type that can be trivially copied and has a standard layout.
 * @tparam Type Type to check.
 */
template <typename Type>
concept pod_type = std::is_trivially_copyable_v<Type> && std::is_standard_layout_v<Type>;

/**
 * Standard conformant allocator. As an extra imogrify requirement, it must also be an empty type.
 * @tparam Allocator Type to check.
 */
template <typename Allocator>
concept standard_empty_allocator =
		std::is_nothrow_constructible_v<Allocator> && std::is_nothrow_copy_constructible_v<Allocator> &&
		std::is_nothrow_destructible_v<Allocator> && std::is_empty_v<Allocator> &&
		std::is_invocable_v<decltype(&Allocator::allocate), Allocator, std::size_t> &&
		std::is_invocable_v<
				decltype(&Allocator::deallocate), Allocator,
				std::invoke_result_t<decltype(&Allocator::allocate), Allocator, std::size_t>, std::size_t>;

} // namespace imfy