/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/raw_image.hpp"

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <span>

namespace imfy::image::detail
{

void initialize_raw_data(
		initialization initialization_type, std::uint8_t channels, std::uint8_t bit_depth, std::span<std::uint8_t> raw_data
)
{
	switch (initialization_type)
	{
		case initialization::zero:
			std::memset(raw_data.data(), 0, raw_data.size());
			break;

		case initialization::modulo:
			constexpr std::array<std::uint8_t, 4U> channel_modulo{251U, 241U, 239U, 233U};
			const std::size_t byte_depth = bit_depth / 8U;
			for (std::size_t index = 0U; index < raw_data.size(); index += channels * byte_depth)
			{
				for (std::size_t channel_index = 0U; channel_index < channels; ++channel_index)
				{
					for (std::size_t byte_index = 0U; byte_index < byte_depth; ++byte_index)
					{
						const auto value_index = index + (byte_depth * channel_index) + byte_index;
						raw_data[value_index] = static_cast<std::uint8_t>(value_index % channel_modulo[channel_index]);
					}
				}
			}
			break;
	}
}

} // namespace imfy::image::detail