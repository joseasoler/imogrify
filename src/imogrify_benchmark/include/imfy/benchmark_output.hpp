/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_result.hpp>
#include <imfy/vector.hpp>

#include <memory>
#include <span>

namespace imfy::bench
{

enum class renderer : std::uint8_t
{
	markdown, // Context data and benchmark results in a markdown file.
	csv				// CSV table with all benchmark results.
};

class benchmark_output final
{
public:
	benchmark_output(std::span<const renderer> renderers);
	benchmark_output(const benchmark_output&) = delete;
	benchmark_output(benchmark_output&&) noexcept = default;
	benchmark_output& operator=(const benchmark_output&) = delete;
	benchmark_output& operator=(benchmark_output&&) noexcept = default;
	~benchmark_output();

	/**
	 * Generates output for a benchmark result.
	 * @param result Result to be rendered.
	 */
	void output(const result& result);

private:
	vector<std::unique_ptr<class benchmark_renderer>> renderers_;
};

}
