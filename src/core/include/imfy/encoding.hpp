/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

namespace imfy
{

/**
 * Configures terminal output for the current platform.
 * @return True if the operation succeeded.
 */
[[nodiscard]] bool set_terminal();

}
