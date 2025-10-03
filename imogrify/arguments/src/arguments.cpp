/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/arguments.hpp"

#include <imfy/build.hpp>

#include <CLI/CLI.hpp>

#include <span>

namespace
{

void define_arguments(CLI::App& app, imfy::arguments::data& data)
{
	using namespace imfy::core::build;
	app.name(std::string{project.name});
	app.description(std::string{project.description});
	app.add_flag("--br,--build-report", data.build_report, "Report build metadata and runtime hardware.");
}

}

namespace imfy::arguments
{
result_t parse(std::span<const char*> arguments)
{
	CLI::App app{};
	data data{};

	try
	{
		define_arguments(app, data);
		app.parse(static_cast<int>(arguments.size()), arguments.data());
	}
	catch (const CLI::Error& exc)
	{
		// CLI11 prints its own errors in this call.
		return parse_exit_code{.exit_code = app.exit(exc)};
	}

	return data;
}
}
