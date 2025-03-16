/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_parameters.hpp>
#include <imfy/image_format.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

namespace imfy::bench
{

/** Defines all the input values to use for a specific benchmark run. */
struct definition final
{
	format_t format;
	operation_t operation;
	vector<library_t> libraries;
	image::channel_t channels;
	image::bit_depth_t bit_depth;
	image_gen_t image_gen;
	size_gen_t size;
	image::compression_t compression;
	/** Benchmark definitions are executed in their sorting order. */
	constexpr auto operator<=>(const definition&) const noexcept = default;
};

}
