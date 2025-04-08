/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>

#include <tl/expected.hpp>

#include <cstdint>
#include <string_view>

namespace imfy::fs
{

using path_view = std::string_view;

enum class error_code : std::uint8_t
{
	unknown = 1U,
	/** Error during file status retrieval. */
	invalid_file_status,
	/** Provided directory path is not a directory. */
	invalid_directory,
	/** The path is already in use in the filesystem. */
	path_in_use,
	/** Could not create a new directory or file. */
	creation_error,
	/** Error while writing a file to disk. */
	write_error,
};

[[nodiscard]] std::string_view error_description(error_code code) noexcept;

/**
 * Creates a directory including parent directories if they do not exist.
 * @param directory Directory path.
 * @return True if it was created, false if a directory with the same path already existed, or an error code.
 */
[[nodiscard]] tl::expected<bool, error_code> create_directories(path_view directory) noexcept;

/**
 * Save data as a file.
 * @param directory Path that will contain the file. Assumed to exist in the filesystem and to be a directory.
 * @param file Name of the file to be saved. Will be overwritten if it exists.
 * @param data Data to be saved in the file.
 * @return Error if the file could not be saved.
 */
[[nodiscard]] tl::expected<void, error_code> save_file(
		path_view directory, path_view file, aligned_span<const std::uint8_t> data
) noexcept;

}
