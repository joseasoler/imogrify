/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>

#include <cstdint>
#include <filesystem>

namespace imfy::fs
{

/**
 * Save data as a file.
 * @param path Path to use for the file.
 * @param data Data to be saved.
 * @return False if the file could not be saved.
 */
bool save(const std::filesystem::path& path, aligned_span<const std::uint8_t> data);

}
