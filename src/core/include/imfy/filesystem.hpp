/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>

#include <tl/expected.hpp>

#include <cstdint>
#include <filesystem>
#include <string_view>

namespace imfy::fs
{

enum class error_code : std::uint8_t
{
	success,
	stream_error,
	input_output_failed,
	end_of_file,
	unknown_error
};

[[nodiscard]] std::string_view to_error_description(error_code code) noexcept;

/**
 * Save data as a file.
 * @param path Path to use for the file.
 * @param data Data to be saved.
 * @return Error if the file could not be saved.
 */
tl::expected<void, error_code> save(const std::filesystem::path& path, aligned_span<const std::uint8_t> data);

}
