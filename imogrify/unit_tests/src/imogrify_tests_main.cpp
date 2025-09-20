/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/platform.hpp>

#include <cstdlib>

#include <catch2/catch_session.hpp>

int main(const int argc, char** argv)
{
	if (!imfy::core::platform::initialize())
	{
		return EXIT_FAILURE;
	}
	return Catch::Session().run(argc, argv);
}
