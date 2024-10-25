/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/concepts.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>

#include <array>
#include <cstddef>
#include <limits>

namespace imfy::image
{

enum class initialization : std::uint8_t
{
	/** Sets all values of the image to zero. */
	zero,
	/** Initializes each pixel component with a value dependent on the pixel index. Intended for testing. */
	modulo,
};

namespace detail
{
template <std::uint8_t Channels>
concept valid_channel_count = Channels > 0U && Channels <= 4U;

template <std::uint8_t BitDepth>
concept valid_bit_depth_count = BitDepth == 8U || BitDepth == 16U;

void initialize_raw_data(
		initialization initialization_type, std::uint8_t channels, std::uint8_t bit_depth, std::span<std::uint8_t> raw_data
);

} // namespace detail

template <std::uint8_t Channels, std::uint8_t BitDepth>
	requires detail::valid_channel_count<Channels> && detail::valid_bit_depth_count<BitDepth>
class raw_image final
{
public:
	using value_type = std::conditional_t<BitDepth == 16U, std::uint16_t, std::uint8_t>;
	static constexpr std::uint8_t channels{Channels};
	static constexpr std::uint8_t bit_depth{BitDepth};

	explicit raw_image(const image_size& img_size)
		: width_{img_size.width}
		, height_{img_size.height}
		, data_(static_cast<std::size_t>(width_ * height_) * channels)
	{
	}

	raw_image(const image_size& img_size, initialization initialization_type)
		: raw_image(img_size)
	{
		detail::initialize_raw_data(initialization_type, channels, bit_depth, raw_data());
	}

	raw_image() = delete;
	raw_image(const raw_image&) = delete;
	raw_image(raw_image&&) noexcept = default;
	raw_image& operator=(const raw_image&) = delete;
	raw_image& operator=(raw_image&&) noexcept = default;
	~raw_image() = default;

	[[nodiscard]] std::uint16_t width() const noexcept { return width_; }
	[[nodiscard]] std::uint16_t height() const noexcept { return height_; }
	[[nodiscard]] std::span<value_type> data() noexcept { return data_.span(); }
	[[nodiscard]] std::span<const value_type> data() const noexcept { return data_.span(); }
	[[nodiscard]] std::span<std::uint8_t> raw_data() noexcept
	{
		const auto data_span = data();
		return {reinterpret_cast<std::uint8_t*>(data_span.data()), data_span.size() * sizeof(value_type)};
	}
	[[nodiscard]] std::span<const std::uint8_t> raw_data() const noexcept
	{
		const auto data_span = data();
		return {reinterpret_cast<const std::uint8_t*>(data_span.data()), data_span.size() * sizeof(value_type)};
	}

private:
	std::uint16_t width_;
	std::uint16_t height_;
	imfy::memory_block<value_type> data_;
};

} // namespace imfy::image
