/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_images.hpp"

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
#include <magic_enum.hpp>

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

image_size image_size_from_def(size_def def)
{
	constexpr std::uint16_t small_side{64U};
	constexpr std::uint16_t large_side{2048U};
	return image_size(
			(def == size_def::small || def == size_def::tall) ? small_side : large_side,
			(def == size_def::small || def == size_def::wide) ? small_side : large_side
	);
}

raw_image get_zero_image(const channel_t channels, const bit_depth_t bit_depth, const image_size img_size)
{
	raw_image image(channels, bit_depth, img_size);
	auto* data_ptr = image.data().as_writable_bytes().data();
	std::memset(data_ptr, 0, image.data().size_bytes());
	return image;
}

raw_image get_modulo_image(const channel_t channels, const bit_depth_t bit_depth, const image_size img_size)
{
	raw_image image(channels, bit_depth, img_size);
	constexpr std::array<std::uint8_t, 4U> byte_modulo{251U, 241U, 239U, 233U};

	std::size_t value_index{0U};
	auto* data_ptr = image.data().as_writable_bytes().data();
	const auto* data_end = data_ptr + image.data().size_bytes();
	const auto channels_value = static_cast<std::size_t>(channels);
	for (; data_ptr != data_end; ++data_ptr, ++value_index)
	{
		*data_ptr = static_cast<std::uint8_t>(value_index % byte_modulo[value_index % channels_value]);
	}

	return image;
}

raw_image get_random_image(const channel_t channels, const bit_depth_t bit_depth, const image_size img_size)
{
	raw_image image(channels, bit_depth, img_size);

	// Generate the same image for each combination of input parameters. Since <random> is not deterministic across
	// implementations, different standard libraries will generate different images.
	const std::uint32_t seed =
			((static_cast<std::uint32_t>(channels) << 16U) | static_cast<std::uint32_t>(bit_depth)) ^
			((static_cast<std::uint32_t>(img_size.width) << 16U) | static_cast<std::uint32_t>(img_size.height));
	std::mt19937 prng{seed};
	// uint8_t is explicitly excluded by the standard, see https://eel.is/c++draft/rand.req.genl#1.6.
	std::uniform_int_distribution<std::uint16_t> uniform_dist{0U, std::numeric_limits<std::uint8_t>::max()};

	auto* data_ptr = image.data().as_writable_bytes().data();
	const auto* data_end = data_ptr + image.data().size_bytes();
	for (; data_ptr != data_end; ++data_ptr)
	{
		*data_ptr = static_cast<std::uint8_t>(uniform_dist(prng));
	}

	return image;
}

using imfy::bench::image_gen_def;

constexpr std::array<raw_image (*)(channel_t, bit_depth_t, image_size), magic_enum::enum_count<image_gen_def>()>
		image_generators{get_zero_image, get_modulo_image, get_random_image};

constexpr std::size_t image_not_found = std::numeric_limits<std::size_t>::max();

// Simple linear search, as the total number of input images should remain small.
std::size_t position_of_image(
		const imfy::vector<imfy::bench::benchmark_image_data>& images, const imfy::bench::definition& def,
		image_size img_size
)
{
	for (std::size_t position{0U}; position < images.size(); ++position)
	{
		const auto& image_data = images[position];
		if (image_data.image_gen_ == def.image_gen && image_data.image_.channels() == def.channels &&
				image_data.image_.bit_depth() == def.bit_depth && image_data.image_.size() == img_size)
		{
			return position;
		}
	}
	return image_not_found;
}

} // namespace

namespace imfy::bench
{

benchmark_image_data::benchmark_image_data(const imfy::bench::definition& def, const image_size img_size)
	: image_gen_{def.image_gen}
	, image_{image_generators[static_cast<std::size_t>(def.image_gen)](def.channels, def.bit_depth, img_size)}
	, filename_{fmt::format(
				"imfy_{:d}_{:d}_{:s}_{:d}_{:d}.png", static_cast<int>(def.channels), static_cast<int>(def.bit_depth),
				magic_enum::enum_name(def.image_gen), img_size.width, img_size.height
		)}
{
}

benchmark_images::benchmark_images(std::span<const definition> definitions)
{
	for (const definition& def : definitions)
	{
		const image_size img_size = image_size_from_def(def.size);
		const auto position = position_of_image(images_, def, img_size);
		if (position == image_not_found)
		{
			images_.emplace_back(def, img_size);
		}
	}
}

bool benchmark_images::save_all(const std::filesystem::path& path) const
{
	for (std::size_t img_index{0U}; img_index < images_.size(); ++img_index)
	{
		const auto& image_data = images_[img_index];
		const auto encoded = imfy::png::encode(
				png::to_color_type(image_data.image_.channels()), image_data.image_.bit_depth(), image_data.image_.size(),
				image_data.image_.data(), compression_t::standard
		);
		if (!encoded.has_value())
		{
			return false;
		}
		const aligned_span span{encoded.value().memory.span().data(), encoded.value().size};
		const auto file_path = path / image_data.filename_;
		if (!fs::save(file_path, span))
		{
			return false;
		}
	}
	return true;
}

const raw_image* benchmark_images::get(const definition def) const noexcept
{
	const image_size img_size = image_size_from_def(def.size);
	const auto position = position_of_image(images_, def, img_size);
	return position != image_not_found ? &images_[position].image_ : nullptr;
}

} // namespace imfy::bench