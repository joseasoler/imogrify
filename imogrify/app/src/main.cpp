/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/assert.hpp>
#include <imfy/platform.hpp>

#include <cstdlib>

int main([[maybe_unused]] const int argc, [[maybe_unused]] const char** argv)
{
	if (!imfy::core::platform::initialize())
	{
		IMFY_ASSERT(false);
		return EXIT_FAILURE;
	}
	IMFY_ASSUME(argv != nullptr);
	IMFY_ASSERT(argc == 3);

	return EXIT_SUCCESS;
}
