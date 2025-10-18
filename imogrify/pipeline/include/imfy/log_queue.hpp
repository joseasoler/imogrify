/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/concurrent_queue.hpp>
#include <imfy/fundamental.hpp>
#include <imfy/log_level.hpp>

#include <chrono>
#include <string>
#include <string_view>
#include <vector>

namespace imfy::pipeline
{

/**
 * Multi-producer, single-consumer log storage.
 * Operations are thread-safe unless explicitly mentioned.
 */
class log_queue final
{
public:
	using producer_token_t = core::concurrentqueue::producer_token<log_queue>;
	using consumer_token_t = core::concurrentqueue::consumer_token<log_queue>;

	/**
	 * Constructing a log queue is not thread safe.
	 * @param min_level Minimum log level to accept at runtime.
	 */
	explicit log_queue(report::log_level min_level);
	/** Log queue destruction is not thread safe. */
	~log_queue() = default;
	log_queue(const log_queue&) = delete;
	log_queue(log_queue&&) noexcept = delete;
	log_queue& operator=(const log_queue&) = delete;
	log_queue& operator=(log_queue&&) noexcept = delete;

	/** Log reporters must own a token. */
	[[nodiscard]] producer_token_t create_producer_token();
	/** Log consumer must own a token. */
	[[nodiscard]] consumer_token_t create_consumer_token();

	/**
	 * Enqueue a new log.
	 * @param token Token owned by the worker creating the log.
	 * @param worker_name Name of the worker creating the log.
	 * @param lvl Log level to use.
	 * @param text Text to report back to the user.
	 */
	void add_log(
			const producer_token_t& token, std::string_view worker_name, report::log_level lvl, std::string_view text
	);

	/**
	 * Enqueue a new log. Ignored when NDEBUG is defined unless IMOGRIFY_SHOW_DEBUG_LOGS is set to ON.
	 * @param token Token owned by the worker creating the log.
	 * @param worker_name Name of the worker creating the log.
	 * @param lvl Log level to use.
	 * @param text Text to report back to the user.
	 */
	void add_debug_log(
			const producer_token_t& token, std::string_view worker_name, report::log_level lvl, std::string_view text
	);

	/**
	 * Checks if logs should be processed.
	 * @param token Token owned by the log consumer.
	 * @return true if there is at least one log in the queue.
	 * @return false if there are no logs waiting in the queue.
	 */
	[[nodiscard]] bool pending_logs(const consumer_token_t& token) const;

	/**
	 * Retrieve pending logs from the queue.
	 * @param token Token owned by the log consumer.
	 * @param container Pending logs will be inserted at the end of this container.
	 */
	void take_logs(consumer_token_t& token, std::vector<std::string>& container);

private:
	using clock = std::chrono::steady_clock;
	moodycamel::ConcurrentQueue<std::string> _logs;
	clock::time_point _start_time;
	uint8_t _min_level{0U};
#if !defined(NDEBUG)
	bool _generated_consumer_token;
#endif
};

}
