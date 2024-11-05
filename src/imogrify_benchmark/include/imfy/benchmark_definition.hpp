/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_parameters.hpp>

#include <compare>
#include <cstdint>

namespace imfy::bench
{

/** Defines all of the input values to use for a specific benchmark run. */
struct definition final
{
	format_def format;
	operation_def operation;
	library_flags libraries;
	std::uint8_t channels;
	std::uint8_t bit_depth;
	size_def size;
	std::int32_t compression;
	/** Benchmark definitions are executed in their sorting order. */
	constexpr auto operator<=>(const definition&) const noexcept = default;
};

} // namespace imfy::bench