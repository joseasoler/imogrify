/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
