/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/worker.hpp>

namespace imfy::worker
{

/**
 * @brief Reports information and issues back to the user.
 * Owns standard output and standard error.
 */
class reporter final : public worker
{
public:
	reporter();

	reporter(const reporter&) = delete;
	reporter(reporter&&) noexcept = default;
	reporter& operator=(const reporter&) = delete;
	reporter& operator=(reporter&&) noexcept = default;
	~reporter() override = default;
};

}
