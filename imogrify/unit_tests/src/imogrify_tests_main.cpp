/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/platform.hpp>

#include <fmt/base.h>

#include <cstdlib>

#include <catch2/catch_session.hpp>

int main(const int argc, char** argv)
{
	if (const char* error_message = imfy::core::platform::initialize(); error_message != nullptr)
	{
		fmt::println(stderr, "{:s}", error_message);
		return EXIT_FAILURE;
	}

	return Catch::Session().run(argc, argv);
}
