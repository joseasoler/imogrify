/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/build.hpp>
#include <imfy/markdown.hpp>

#include <fmt/base.h>
#include <nowide/args.hpp>

#include <cstdlib>

int main(int argc, char* argv[])
{
	const nowide::args nowide_args{argc, argv};
	imfy::markdown mark;
	mark.add_heading(imfy::markdown::heading::level_1, imfy::build::project.name);
	mark.add_heading(imfy::markdown::heading::level_2, "dependencies");

	for (const auto& dependency : imfy::build::dependencies)
	{
		mark.add_heading(imfy::markdown::heading::level_3, dependency.name);
	}
	fmt::println("{:s}", mark.view());
	return EXIT_SUCCESS;
}