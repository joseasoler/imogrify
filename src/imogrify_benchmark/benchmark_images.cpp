/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_images.hpp"

#include <imfy/assert.hpp>
#include <imfy/attributes.hpp>
#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_parameters.hpp>
#include <imfy/filesystem.hpp>
#include <imfy/image_format.hpp>
#include <imfy/image_size.hpp>
#include <imfy/png_encoder.hpp>
#include <imfy/png_format.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/vector.hpp>

#include <fmt/format.h>

#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <filesystem>
#include <limits>
#include <random>
#include <span>

namespace
{

using namespace imfy::bench;
using namespace imfy::image;

image_size image_size_from_def(const size_gen_t def) noexcept
{
	constexpr std::uint16_t small_side{64U};
	constexpr std::uint16_t large_side{1024U};
	return image_size(
			def == size_gen_t::small || def == size_gen_t::tall ? small_side : large_side,
			def == size_gen_t::small || def == size_gen_t::wide ? small_side : large_side
	);
}

void set_zero_image(std::uint8_t* const IMFY_RESTRICT data_ptr, const std::uint8_t* const IMFY_RESTRICT data_end)
{
	std::memset(data_ptr, 0, static_cast<std::size_t>(data_end - data_ptr));
}

void set_modulo_image(
		std::uint8_t* IMFY_RESTRICT data_ptr, const std::uint8_t* IMFY_RESTRICT data_end, const channel_t channels
) noexcept
{
	constexpr std::array<std::uint8_t, 4U> byte_modulo{251U, 241U, 239U, 233U};
	std::size_t value_index{0U};
	const auto channels_value = static_cast<std::size_t>(channels);
	for (; data_ptr != data_end; ++data_ptr, ++value_index)
	{
		*data_ptr = static_cast<std::uint8_t>(value_index % byte_modulo[value_index % channels_value]);
	}
}

void set_random_image(
		std::uint8_t* IMFY_RESTRICT data_ptr, const std::uint8_t* IMFY_RESTRICT data_end, const std::uint32_t seed
)
{
	std::mt19937 prng{seed};
	// uint8_t is explicitly excluded by the standard, see https://eel.is/c++draft/rand.req.genl#1.6.
	std::uniform_int_distribution<std::uint16_t> uniform_dist{0U, std::numeric_limits<std::uint8_t>::max()};
	for (; data_ptr != data_end; ++data_ptr)
	{
		*data_ptr = static_cast<std::uint8_t>(uniform_dist(prng));
	}
}

raw_image generate_image(
		const image_gen_t generation, const channel_t channels, const bit_depth_t bit_depth, const image_size img_size
)
{
	raw_image image(channels, bit_depth, img_size);
	auto* IMFY_RESTRICT data_ptr = image.data().as_writable_bytes().data();
	const auto* IMFY_RESTRICT data_end = data_ptr + image.data().size_bytes();
	switch (generation)
	{
		case image_gen_t::zero:
			set_zero_image(data_ptr, data_end);
			break;
		case image_gen_t::modulo:
			set_modulo_image(data_ptr, data_end, channels);
			break;
		case image_gen_t::random:
		{
			// Generate the same image for each combination of input parameters.
			const std::uint32_t seed =
					(static_cast<std::uint32_t>(channels) << 16U | static_cast<std::uint32_t>(bit_depth)) ^
					(static_cast<std::uint32_t>(img_size.width) << 16U | static_cast<std::uint32_t>(img_size.height));
			set_random_image(data_ptr, data_end, seed);
			break;
		}
	}

	return image;
}

constexpr std::size_t image_not_found = std::numeric_limits<std::size_t>::max();

// Simple linear search, as the total number of input images should remain small.
std::size_t position_of_image(
		const imfy::vector<benchmark_image_data>& images, const definition& def, const image_size img_size
) noexcept
{
	for (std::size_t position{0U}; position < images.size(); ++position)
	{
		if (const auto& image_data = images[position];
				image_data.image_gen_ == def.image_gen && image_data.image_.channels() == def.channels &&
				image_data.image_.bit_depth() == def.bit_depth && image_data.image_.size() == img_size)
		{
			return position;
		}
	}
	return image_not_found;
}

}

namespace imfy::bench
{

benchmark_image_data::benchmark_image_data(const definition& def, const image_size img_size)
	: image_gen_{def.image_gen}
	, image_{generate_image(image_gen_, def.channels, def.bit_depth, img_size)}
	, filename_{fmt::format(
				"imfy_{:d}_{:d}_{:s}_{:d}_{:d}.png", static_cast<int>(def.channels), static_cast<int>(def.bit_depth),
				image_gen_string(image_gen_), img_size.width, img_size.height
		)}
{
}

benchmark_images::benchmark_images(const std::span<const definition> definitions)
{
	for (const definition& def : definitions)
	{
		const image_size img_size = image_size_from_def(def.size);
		if (const auto position = position_of_image(images_, def, img_size); position == image_not_found)
		{
			images_.emplace_back(def, img_size);
		}
	}
}

bool benchmark_images::save(const std::filesystem::path& path) const
{
	for (std::size_t img_index{0U}; img_index < images_.size(); ++img_index)
	{
		const auto& image_data = images_[img_index];
		const auto encoded = encode(
				png::to_color_type(image_data.image_.channels()), image_data.image_.bit_depth(), image_data.image_.size(),
				image_data.image_.data(), compression_t::standard
		);

		if (!encoded.has_value()) [[unlikely]]
		{
			return false;
		}

		const aligned_span span{encoded.value().data(), encoded.value().size()};
		if (const auto file_path = path / image_data.filename_; !fs::save(file_path, span))
		{
			return false;
		}
	}

	return true;
}

const raw_image& benchmark_images::get(const definition& def) const noexcept
{
	const image_size img_size = image_size_from_def(def.size);
	const auto position = position_of_image(images_, def, img_size);
	IMFY_ASSUME(position < images_.size());
	return images_[position].image_;
}

}
