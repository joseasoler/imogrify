/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/fundamental.hpp>
#include <imfy/log_level.hpp>
#include <imfy/pipeline.hpp>
#include <imfy/worker.hpp>

#include <memory>
#include <vector>

#if !defined(NDEBUG)
#include <thread>
#endif

namespace imfy::worker
{

/**
 * @brief Manages workers and items to be worked.
 * Owns filesystem I/O.
 */
class supervisor final
{
public:
	supervisor(size_t max_workers, report::log_level min_log_level);

	supervisor(const supervisor&) = delete;
	supervisor(supervisor&&) noexcept = delete;
	supervisor& operator=(const supervisor&) = delete;
	supervisor& operator=(supervisor&&) noexcept = delete;
	~supervisor() = default;

private:
	// ToDo
	[[maybe_unused]] size_t _max_workers;
	pipeline::pipeline _pipeline;
#if !defined(NDEBUG)
	// Assert thread ownership.
	std::thread::id _thread_id;
#endif
	std::vector<std::unique_ptr<worker>> _workers;
};

}
