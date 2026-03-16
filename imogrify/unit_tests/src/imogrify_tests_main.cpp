/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
