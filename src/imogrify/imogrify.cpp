/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/build.hpp>
#include <imfy/markdown.hpp>
#include <imfy/runtime.hpp>

#include <cstdlib>
#include <iostream>

int main(int /*argc*/, char** /*argv*/)
{
	imfy::markdown mark{std::cout};
	mark.add_heading(imfy::markdown::heading::level_1, imfy::build::project.name);
	mark.add_heading(imfy::markdown::heading::level_2, "dependencies");

	for (const auto& dependency : imfy::build::dependencies)
	{
		mark.add_heading(imfy::markdown::heading::level_3, dependency.name);
	}

	mark.add_heading(imfy::markdown::heading::level_2, "Runtime information");
	mark.add_heading(imfy::markdown::heading::level_3, "Supported SIMD");
	for (const auto& simd_target : imfy::runtime::simd_target_names())
	{
		mark.add_heading(imfy::markdown::heading::level_4, simd_target);
	}
	return EXIT_SUCCESS;
}