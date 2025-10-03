/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/fundamental.hpp>

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

}
