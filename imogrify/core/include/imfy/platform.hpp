/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

namespace imfy::core::platform
{

/**
 * Platform-specific initialization steps.
 * @return Null pointer if the operation succeeded. Error string otherwise.
 */
[[nodiscard]] const char* initialize() noexcept;

}
