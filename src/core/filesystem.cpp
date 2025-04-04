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

namespace
{
constexpr imfy::fs::error_code to_error_code(const std::ios::iostate state)
{
	IMFY_ASSUME(state != std::ios::goodbit);
	if (state == std::ios::badbit)
	{
		return imfy::fs::error_code::stream_error;
	}
	if (state == std::ios::failbit)
	{
		return imfy::fs::error_code::input_output_failed;
	}
	if (state == std::ios::eofbit)
	{
		return imfy::fs::error_code::end_of_file;
	}
	return imfy::fs::error_code::unknown_error;
}
}

namespace imfy::fs
{

std::string_view to_error_description(const error_code code) noexcept
{
	IMFY_ASSUME(code != error_code::success);
	switch (code)
	{
		case error_code::stream_error:
			return "irrecoverable stream error";
		case error_code::input_output_failed:
			return "input/output operation failed";
		case error_code::end_of_file:
			return "sequence has reached end-of-file";
		[[unlikely]] case error_code::success:
			[[fallthrough]];
		[[unlikely]] case error_code::unknown_error:
			[[fallthrough]];
		[[unlikely]] default:
			return "unknown error";
	}
}

tl::expected<void, error_code> save(const std::filesystem::path& path, const aligned_span<const std::uint8_t> data)
{
	// NOLINTNEXTLINE(hicpp-signed-bitwise)
	constexpr auto open_mode = std::ios::out | std::ios::binary;
	std::ofstream ofstr{path, open_mode};
	if (!ofstr.good())
	{
		return tl::make_unexpected(to_error_code(ofstr.rdstate()));
	}

	// NOLINTNEXTLINE(cppcoreguidelines-pro-type-reinterpret-cast)
	const auto* memory_begin = reinterpret_cast<const char*>(data.data());
	ofstr.write(memory_begin, static_cast<std::ptrdiff_t>(data.size()));

	if (!ofstr.good())
	{
		return tl::make_unexpected(to_error_code(ofstr.rdstate()));
	}

	return {};
}

}
