/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_images.hpp"

#include <imfy/benchmark_definition.hpp>
#include <imfy/benchmark_parameters.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/vector.hpp>

#include <array>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <span>
#include <string_view>

namespace
{

using imfy::bench::size_def;
imfy::image_size image_size_from_def(size_def def)
{
	constexpr std::uint16_t small_side{64U};
	constexpr std::uint16_t large_side{2048U};
	return imfy::image_size(
			(def == size_def::small || def == size_def::tall) ? small_side : large_side,
			(def == size_def::small || def == size_def::wide) ? small_side : large_side
	);
}

constexpr std::size_t image_not_found = std::numeric_limits<std::size_t>::max();

// Simple linear search, as the total number of input images should remain small.
std::size_t position_of_image(
		const imfy::vector<imfy::raw_image>& images, std::uint8_t channels, std::uint8_t bit_depth,
		imfy::image_size img_size
)
{
	for (std::size_t position{0U}; position < images.size(); ++position)
	{
		const auto& image = images[position];
		if (image.channels() == channels && image.bit_depth() == bit_depth && image.size() == img_size)
		{
			return position;
		}
	}
	return image_not_found;
}

// Generates an image in memory for benchmarking purposes. Does not handle endianness.
imfy::raw_image get_modulo_image(
		const std::uint8_t channels, const std::uint8_t bit_depth, const imfy::image_size img_size
)
{
	imfy::raw_image image(channels, bit_depth, img_size);
	constexpr std::array<std::uint8_t, 4U> byte_modulo{251U, 241U, 239U, 233U};

	std::size_t value_index{0U};
	auto* data_ptr = image.data().as_writable_bytes().data();
	const auto* data_end = data_ptr + image.data().size_bytes();
	for (; data_ptr != data_end; ++data_ptr, ++value_index)
	{
		*data_ptr = static_cast<std::uint8_t>(value_index % byte_modulo[value_index % 4U]);
	}

	return image;
}

void save_reference_image(const imfy::raw_image& /*image*/, std::string_view /*path*/)
{
	// ToDo filesystem implementation.
}

} // namespace

namespace imfy::bench
{

benchmark_images::benchmark_images(std::span<const definition> definitions, std::string_view path)
{
	for (const definition& def : definitions)
	{
		const image_size img_size = image_size_from_def(def.size);
		const auto position = position_of_image(images_, def.channels, def.bit_depth, img_size);
		if (position == image_not_found)
		{
			images_.push_back(get_modulo_image(def.channels, def.bit_depth, img_size));
			save_reference_image(images_.back(), path);
		}
	}
}

const raw_image* benchmark_images::get(const std::uint8_t channels, const std::uint8_t bit_depth, const size_def size)
		const noexcept
{
	const image_size img_size = image_size_from_def(size);
	const auto position = position_of_image(images_, channels, bit_depth, img_size);
	return position != image_not_found ? &images_[position] : nullptr;
}

} // namespace imfy::bench