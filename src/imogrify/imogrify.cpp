/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <imfy/character_encoding.hpp>

#if IMOGRIFY_USE_FMT_BASE_HEADER
#include <fmt/base.h>
#else
// Older versions of fmt lack the fmt/base.h header.
#include <fmt/ostream.h>
#endif // #if IMOGRIFY_USE_FMT_BASE_HEADER

#include <cstdlib>

int main(int /*argc*/, char** /*argv*/)
{
	if (const auto encoding_result = imfy::character_encoding::initialize(); !encoding_result)
	{
		fmt::print("{}", encoding_result.error());
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}
