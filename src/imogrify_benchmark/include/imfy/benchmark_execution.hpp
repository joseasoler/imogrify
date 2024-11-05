/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_images.hpp>
#include <imfy/benchmark_result.hpp>

#include <memory>

namespace ankerl::nanobench
{
class Bench;
} // namespace ankerl::nanobench

namespace imfy::bench
{

class benchmark_execution final
{
public:
	explicit benchmark_execution(const benchmark_images& images);
	benchmark_execution(const benchmark_execution&) = delete;
	benchmark_execution(benchmark_execution&&) noexcept = delete;
	benchmark_execution& operator=(const benchmark_execution&) = delete;
	benchmark_execution& operator=(benchmark_execution&&) noexcept = delete;
	~benchmark_execution();

	/**
	 * Executes a benchmark and generates its results.
	 * @param def Definition to be executed.
	 * @return Results for each definition.
	 */
	result run(const definition& def);

private:
	std::unique_ptr<ankerl::nanobench::Bench> bench_;
	const benchmark_images& images_;
};

} // namespace imfy::bench