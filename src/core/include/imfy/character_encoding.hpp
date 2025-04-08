/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <tl/expected.hpp>

#include <string_view>

namespace imfy::character_encoding
{

/**
 * Sets up UTF-8 character for the current platform.
 * @return Error description if the operation failed.
 */
[[nodiscard]] tl::expected<void, std::string_view> initialize() noexcept;

}
