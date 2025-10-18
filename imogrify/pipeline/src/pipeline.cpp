/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/pipeline.hpp"

#include <imfy/log_level.hpp>
#include <imfy/log_queue.hpp>

namespace imfy::pipeline
{

pipeline::pipeline(const report::log_level min_log_level)
	: _log_queue(min_log_level)
{
}

log_queue& pipeline::get_log_queue() noexcept
{
	return _log_queue;
}

}
