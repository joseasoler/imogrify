/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/supervisor.hpp"

#include <imfy/fundamental.hpp>
#include <imfy/log_level.hpp>
#include <imfy/reporter.hpp>

#include <memory>
#include <thread>

namespace imfy::worker
{

supervisor::supervisor(const size_t max_workers, const report::log_level min_log_level)
	// The supervisor counts as one of the workers, executed on the main thread.
	: _max_workers{max_workers - 1U}
	, _pipeline(min_log_level)
#if !defined(NDEBUG)
	, _thread_id{std::thread::id()}
#endif
{
	_workers.reserve(max_workers);
	// A reporter must always be available.
	_workers.emplace_back(std::make_unique<reporter>());
}

}
