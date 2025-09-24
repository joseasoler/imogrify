/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>

namespace imfy::core::build
{

/** Version POD based on <A HREF="https://semver.org/">semantic versions</A>. */
struct version_t final
{
	/** Incremented after making incompatible API changes. */
	std::uint16_t major{};
	/** Incremented after adding functionality in a backwards compatible manner. */
	std::uint16_t minor{};
	/** Incremented after making backwards compatible bug fixes. */
	std::uint16_t patch{};
};

}
