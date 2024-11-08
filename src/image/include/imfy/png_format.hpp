/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <cstdint>

namespace imfy::png
{

/** See http://www.libpng.org/pub/png/spec/1.2/PNG-Chunks.html#C.IHDR */
enum class color_type : std::uint8_t
{
	gray = 0U,
	rgb = 2U,
	palette = 3U,
	ga = 4U,
	rgba = 6U,
};

/** See https://www.zlib.net/manual.html */
constexpr auto no_compression = 0;
constexpr auto speed_compression = 1;
constexpr auto default_compression = 6;
constexpr auto best_compression = 9;

/**
 * Maps the channel counts supported by imogrify to PNG color types. Ignores palette.
 * @param channels Channel count.
 * @return Color type.
 */
color_type color_type_from_channels(std::uint8_t channels);

} // namespace imfy::png