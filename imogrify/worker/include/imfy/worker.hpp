/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/fundamental.hpp>

#include <string>
#include <string_view>

namespace imfy::report
{
class report_queue;
}

namespace imfy::worker
{

class worker
{
public:
	explicit worker(std::string name) noexcept;

	worker(const worker&) = delete;
	worker(worker&&) noexcept = default;
	worker& operator=(const worker&) = delete;
	worker& operator=(worker&&) noexcept = default;
	virtual ~worker() = default;

	[[nodiscard]] std::string_view name() const noexcept;

private:
	std::string _name;
};

}
