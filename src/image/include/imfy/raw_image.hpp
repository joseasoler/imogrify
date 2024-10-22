/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/concepts.hpp>
#include <imfy/image_size.hpp>
#include <imfy/memory_block.hpp>

#include <array>
#include <cstring>

namespace imfy::image
{

namespace detail
{
template <std::uint8_t Channels>
concept valid_channel_count = Channels > 0U && Channels <= 4U;

template <std::uint8_t BitDepth>
concept valid_bit_depth_count = BitDepth == 8U || BitDepth == 16U;

template <std::uint8_t BitDepth>
	requires valid_bit_depth_count<BitDepth>
struct bit_depth_underlying_type
{
	using value_type = std::false_type;
};

template <>
struct bit_depth_underlying_type<8U>
{
	using value_type = std::uint8_t;
};

template <>
struct bit_depth_underlying_type<16U>
{
	using value_type = std::uint16_t;
};

} // namespace detail

enum class initialization : std::uint8_t
{
	/** Sets all values of the image to zero. */
	zero,
	/** Initializes each pixel component with a value dependent on the pixel index. Intended for testing. */
	modulo,
};

template <std::uint8_t Channels, std::uint8_t BitDepth>
	requires detail::valid_channel_count<Channels> && detail::valid_bit_depth_count<BitDepth>
class raw_image final
{
public:
	using value_type = typename detail::bit_depth_underlying_type<BitDepth>::value_type;
	static constexpr std::uint8_t channels{Channels};
	static constexpr std::uint8_t bit_depth{BitDepth};
	static constexpr std::size_t pixel_size = channels * bit_depth / 8U;

	/**
	 * Uninitialized raw image.
	 * @param img_size Width and height of the image.
	 */
	explicit raw_image(const image_size& img_size)
		: width_{img_size.width}
		, height_{img_size.height}
		, data_(width_ * height_ * pixel_size)
	{
	}

	raw_image(const image_size& img_size, initialization initialization_type)
		: raw_image(std::move(img_size))
	{
		auto span = data_.span();
		switch (initialization_type)
		{
			case initialization::zero:
				std::memset(span.data(), 0, span.size() * sizeof(value_type));
				break;
			case initialization::modulo:
				constexpr std::array<value_type, 4U> channel_modulo{255U, 254U, 253U, 252U};
				for (std::size_t index = 0U; index < span.size(); index += channels)
				{
					span[index] = static_cast<value_type>(index % channel_modulo[0U]);
					if constexpr (Channels > 1U)
					{
						span[index + 1U] = static_cast<value_type>(index % channel_modulo[1U]);
					}
					if constexpr (Channels > 2U)
					{
						span[index + 2U] = static_cast<value_type>(index % channel_modulo[2U]);
					}
					if constexpr (Channels > 3U)
					{
						span[index + 3U] = static_cast<value_type>(index % channel_modulo[3U]);
					}
				}
				break;
		}
	}

	raw_image() = delete;
	raw_image(const raw_image&) = delete;
	raw_image(raw_image&&) noexcept = default;
	raw_image& operator=(const raw_image&) = delete;
	raw_image& operator=(raw_image&&) noexcept = default;
	~raw_image() = default;

	[[nodiscard]] std::size_t width() const noexcept { return width_; }
	[[nodiscard]] std::size_t height() const noexcept { return height_; }
	[[nodiscard]] std::span<value_type> data() noexcept { return data_.span(); }
	[[nodiscard]] std::span<const value_type> data() const noexcept { return data_.span(); }

private:
	std::size_t width_;
	std::size_t height_;
	imfy::memory_block<value_type> data_;
};

} // namespace imfy::image
