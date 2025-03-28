/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/raw_image.hpp"

#include <imfy/aligned_span.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>

#include <cstddef>

namespace imfy::image
{

raw_image::raw_image(const channel_t channels, const bit_depth_t bit_depth, const image_size img_size)
	: data_(
				static_cast<std::size_t>(img_size.width * img_size.height) * static_cast<std::size_t>(channels) *
				byte_size(bit_depth)
		)
	, image_size_{img_size}
	, channels_{channels}
	, bit_depth_{bit_depth}
{
}

channel_t raw_image::channels() const noexcept
{
	return channels_;
}

bit_depth_t raw_image::bit_depth() const noexcept
{
	return bit_depth_;
}

image_size raw_image::size() const noexcept
{
	return image_size_;
}

aligned_span<raw_image::value_type> raw_image::data() noexcept
{
	return data_.span();
}

aligned_span<const raw_image::value_type> raw_image::data() const noexcept
{
	return data_.span();
}

}
