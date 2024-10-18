/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/markdown.hpp>

#include <fmt/base.h>

#include <cstdlib>

int main()
{
	imfy::markdown mark;
	mark.add_heading(imfy::markdown::heading::level_1, "Hello world!");
	fmt::println("{:s}", mark.view());
	return EXIT_SUCCESS;
}