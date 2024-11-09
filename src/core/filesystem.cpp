/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/filesystem.hpp"

#include <imfy/aligned_span.hpp>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>

namespace imfy::fs
{

bool save(const std::filesystem::path& path, aligned_span<const std::uint8_t> data)
{
	constexpr auto open_mode = std::ios::out | std::ios::binary; // NOLINT
	std::ofstream ofstr{path, open_mode};
	if (!ofstr.is_open())
	{
		return false;
	}
	const auto* memory_begin = reinterpret_cast<const char*>(data.data()); // NOLINT
	ofstr.write(memory_begin, static_cast<std::ptrdiff_t>(data.size()));
	return ofstr.good();
}

} // namespace imfy::fs
