/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/vector.hpp>

#include <memory>

namespace ankerl::nanobench
{
class Bench;
}

namespace imfy::bench
{

class benchmark_execution final
{
public:
	benchmark_execution();
	benchmark_execution(const benchmark_execution&) = delete;
	benchmark_execution(benchmark_execution&&) noexcept = delete;
	benchmark_execution& operator=(const benchmark_execution&) = delete;
	benchmark_execution& operator=(benchmark_execution&&) noexcept = delete;
	~benchmark_execution();

	/**
	 * Executes a benchmark and generates its results.
	 * @param def Definition to be executed.
	 * @param images Pre-generated reference images.
	 * @return Results for each definition.
	 */
	result run(const definition& def, const vector<benchmark_image_data>& images);

private:
	std::unique_ptr<ankerl::nanobench::Bench> bench_;
};

}
