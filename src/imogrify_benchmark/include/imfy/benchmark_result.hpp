/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_parameters.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/vector.hpp>

#include <cstdint>

namespace imfy::bench
{

/** The benchmark definition is executed once for each library. */
struct library_result final
{
	library_t library{};
	double file_size{};
	double file_size_rel{};
	double mpix_second{};
	double milliseconds{};
	double speed_relative{};
	double speed_error{};
	std::uint64_t instructions{};
	std::uint64_t cycles{};
	std::uint64_t branch_instructions{};
	std::uint64_t branch_misses{};
};

/** Results of a single benchmark definition. */
struct result final
{
	format_t format{};
	operation_t operation{};
	image::channel_t channels{};
	image::bit_depth_t bit_depth{};
	image_gen_t image_gen{};
	image::image_size img_size{};
	image::compression_t compression{};
	vector<library_result> library_results{};
};

}
