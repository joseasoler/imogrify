/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/filesystem.hpp"

#include <imfy/aligned_span.hpp>
#include <imfy/assert.hpp>

#include <tl/expected.hpp>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <ios>
#include <string_view>
#include <system_error>

namespace
{
/**
 * Retrieves a file status and return its type while handling any errors.
 * @param path Path to check.
 * @return File type or none if an error occurred.
 */
[[nodiscard]] std::filesystem::file_type get_file_type(const std::filesystem::path& path) noexcept
{
	using namespace std::filesystem;
	std::error_code status_error_code{};
	const file_status status_check = status(path, status_error_code);

	// not_found may set an error code that can be ignored.
	if (status_error_code && status_check.type() != file_type::not_found)
	{
		return file_type::none;
	}

	return status_check.type();
}

}

namespace imfy::fs
{

std::string_view error_description(const error_code code) noexcept
{
	IMFY_ASSERT(code != error_code::unknown);
	switch (code)
	{
		case error_code::invalid_file_status:
			return "file status retrieval error";
		case error_code::invalid_directory:
			return "invalid directory path";
		case error_code::path_in_use:
			return "path is in use";
		case error_code::creation_error:
			return "could not create filesystem entry";
		case error_code::write_error:
			return "file writing error";

		[[unlikely]] case error_code::unknown:
			[[fallthrough]];
		[[unlikely]] default:
			return "unknown error";
	}
}

tl::expected<bool, error_code> create_directories(const path_view directory) noexcept
{
	using namespace std::filesystem;
	const auto directory_type = get_file_type(directory);

	if (directory_type == file_type::none)
	{
		return tl::make_unexpected(error_code::invalid_file_status);
	}
	if (directory_type == file_type::directory)
	{
		return false;
	}
	if (directory_type != file_type::not_found)
	{
		return tl::make_unexpected(error_code::path_in_use);
	}

	try
	{
		// The error_code overload of std::filesystem::create_directories lacks noexcept.
		return std::filesystem::create_directories(directory);
	}
	catch (const filesystem_error&)
	{
		return tl::make_unexpected(error_code::creation_error);
	}
}

tl::expected<void, error_code> save_file(
		const path_view directory, const path_view file, const aligned_span<const std::uint8_t> data
) noexcept
{
	using namespace std::filesystem;

	const path directory_path{directory};
	if (const auto directory_type = get_file_type(directory); directory_type != file_type::directory)
	{
		return tl::make_unexpected(error_code::invalid_directory);
	}

	const auto file_path = directory_path / file;
	const auto file_type = get_file_type(file_path);
	if (file_type == file_type::none)
	{
		return tl::make_unexpected(error_code::invalid_file_status);
	}

	if (file_type != file_type::not_found && file_type != file_type::regular)
	{
		// Allow overwriting if a regular file is found in the path.
		return tl::make_unexpected(error_code::path_in_use);
	}

	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	constexpr auto open_mode = std::ios::out | std::ios::binary;

	std::ofstream ofstream{file_path, open_mode};
	if (!ofstream.good())
	{
		return tl::make_unexpected(error_code::creation_error);
	}

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	const auto* memory_begin = reinterpret_cast<const char*>(data.data());
	ofstream.write(memory_begin, static_cast<std::ptrdiff_t>(data.size()));

	if (!ofstream.good())
	{
		return tl::make_unexpected(error_code::write_error);
	}

	return {};
}

}
