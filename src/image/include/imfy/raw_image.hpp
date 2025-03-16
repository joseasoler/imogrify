/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>

namespace imfy::image
{
class raw_image final
{
public:
	using value_type = std::uint8_t;

	raw_image(channel_t channels, bit_depth_t bit_depth, image_size img_size);

	raw_image() = delete;
	raw_image(const raw_image&) = delete;
	raw_image(raw_image&&) noexcept = default;
	raw_image& operator=(const raw_image&) = delete;
	raw_image& operator=(raw_image&&) noexcept = default;
	~raw_image() = default;

	[[nodiscard]] channel_t channels() const noexcept;
	[[nodiscard]] bit_depth_t bit_depth() const noexcept;
	[[nodiscard]] image_size size() const noexcept;
	[[nodiscard]] aligned_span<value_type> data() noexcept;
	[[nodiscard]] aligned_span<const value_type> data() const noexcept;

private:
	memory_block<value_type> data_;
	image_size image_size_;
	channel_t channels_;
	bit_depth_t bit_depth_;
};

}
