/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/log_level.hpp>
#include <imfy/log_queue.hpp>

namespace imfy::pipeline
{

/**
 * @brief Stores tasks to be performed by workers.
 * Owns worker communication channels.
 */
class pipeline final
{
public:
	explicit pipeline(report::log_level min_log_level);

	pipeline(const pipeline&) = delete;
	pipeline(pipeline&&) noexcept = delete;
	pipeline& operator=(const pipeline&) = delete;
	pipeline& operator=(pipeline&&) noexcept = delete;
	~pipeline() = default;

	log_queue& get_log_queue() noexcept;

private:
	log_queue _log_queue;
};

}
