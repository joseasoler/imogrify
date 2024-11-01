/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/aligned_span.hpp>
#include <imfy/concepts.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>

#include <array>
#include <cstddef>
#include <limits>

namespace imfy
{
class raw_image final
{
public:
	using value_type = std::uint8_t;

	raw_image(std::uint8_t channels, std::uint8_t bit_depth, image_size img_size);

	raw_image() = delete;
	raw_image(const raw_image&) = delete;
	raw_image(raw_image&&) noexcept = default;
	raw_image& operator=(const raw_image&) = delete;
	raw_image& operator=(raw_image&&) noexcept = default;
	~raw_image() = default;

	[[nodiscard]] std::uint8_t channels() const noexcept;
	[[nodiscard]] std::uint8_t bit_depth() const noexcept;
	[[nodiscard]] image_size size() const noexcept;
	[[nodiscard]] aligned_span<raw_image::value_type> data() noexcept;
	[[nodiscard]] aligned_span<const raw_image::value_type> data() const noexcept;

private:
	imfy::memory_block<value_type> data_;
	image_size image_size_;
	std::uint8_t channels_;
	std::uint8_t bit_depth_;
};

} // namespace imfy
