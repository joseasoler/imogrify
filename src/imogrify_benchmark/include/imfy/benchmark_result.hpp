/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_parameters.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/vector.hpp>

#include <chrono>
#include <compare>
#include <cstdint>

namespace imfy::bench
{

/** The benchmark definition is executed once for each library. */
struct library_result final
{
	library_flags library;
	double file_size_relative;
	double mpix_second;
	double speed_relative;
	double speed_error;
	std::uint64_t instructions;
	std::uint64_t cycles;
	std::uint64_t branch_instructions;
	std::uint64_t branch_misses;
};

/** Results of a single benchmark definition. */
struct result final
{
	format_def format;
	operation_def operation;
	std::uint8_t channels;
	std::uint8_t bit_depth;
	image_size img_size;
	std::int32_t compression;
	imfy::vector<library_result> library_results;
};

} // namespace imfy::bench