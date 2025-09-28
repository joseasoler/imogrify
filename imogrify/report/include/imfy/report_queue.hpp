/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/concurrent_queue.hpp>
#include <imfy/fundamental.hpp>

#include <chrono>
#include <string>
#include <string_view>
#include <vector>

namespace imfy::report
{

enum class level : uint8_t
{
	trace, // Detailed reports for the user. Not shown unless explicitly enabled.
	info,	 // Standard reports for the user.
	warn,	 // Minor errors which still allow the input to be processed.
	error, // Error preventing one item from the input from being processed.
	halt,	 // Request to stop the application. Items in progress will be finished first.
	fatal, // Error preventing multiple items from being processed. imogrify will be terminated.
};

/**
 * Multi-producer, single-consumer report storage. Owner thread is always the consumer.
 * Operations are thread-safe unless explicitly mentioned.
 */
class report_queue final
{
public:
	using report_token_t = moodycamel::ProducerToken;

	/**
	 * Constructing a report queue is not thread safe.
	 * @param min_level Minimum report level to accept at runtime.
	 */
	explicit report_queue(level min_level);
	/** Report queue destruction is not thread safe. */
	~report_queue() = default;
	report_queue(const report_queue&) = delete;
	report_queue(report_queue&&) = default;
	report_queue& operator=(const report_queue&) = delete;
	report_queue& operator=(report_queue&&) = default;

	/** To make reports, threads must own a token. */
	[[nodiscard]] report_token_t create_token();

	/**
	 * Enqueue a new report.
	 * @param token Token owned by the thread creating the report.
	 * @param lvl Report level to use.
	 * @param text Text to report back to the user.
	 */
	void make_report(const report_token_t& token, level lvl, std::string_view text);

	/**
	 * Enqueue a new report. Ignored when NDEBUG is defined unless IMOGRIFY_SHOW_DEBUG_REPORTS is set to ON.
	 * @param token Token owned by the thread creating the report.
	 * @param lvl Report level to use.
	 * @param text Text to report back to the user.
	 */
	void make_debug_report(const report_token_t& token, level lvl, std::string_view text);

	/**
	 * Checks if reports should be processed.
	 * @return True if there is at least one report in the queue.
	 */
	[[nodiscard]] bool pending_reports() const;

	/**
	 * Retrieve pending reports from the queue.
	 * @param container Pending reports will be inserted at the end of this container.
	 */
	void take_reports(std::vector<std::string>& container);

private:
	using clock = std::chrono::steady_clock;
	moodycamel::ConcurrentQueue<std::string> _logs;
	moodycamel::ConsumerToken _token;
	clock::time_point _start_time;
	uint8_t _min_level{0U};
};

}
