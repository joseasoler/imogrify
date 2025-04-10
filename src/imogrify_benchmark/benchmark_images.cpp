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
#include <imfy/png.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <fmt/format.h>
#include <tl/expected.hpp>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <limits>
#include <optional>
#include <random>
#include <span>

namespace
{

using namespace imfy::bench;
using namespace imfy::image;

[[nodiscard]] constexpr std::uint64_t id_from_def(const definition& def) noexcept
{
	constexpr auto fields_size = sizeof(format_t) + sizeof(channel_t) + sizeof(bit_depth_t) + sizeof(channel_t) +
															 sizeof(image_gen_t) + sizeof(size_gen_t);

	static_assert(fields_size <= sizeof(std::uint64_t));

	// Definitions with the same values in these fields have the same reference image.
	auto result = static_cast<uint64_t>(def.format);
	result <<= sizeof(format_t);
	result |= static_cast<std::uint64_t>(def.channels);
	result <<= sizeof(channel_t);
	result |= static_cast<std::uint64_t>(def.bit_depth);
	result <<= sizeof(bit_depth_t);
	result |= static_cast<std::uint64_t>(def.image_gen);
	result <<= sizeof(image_gen_t);
	result |= static_cast<std::uint64_t>(def.size);
	return result;
}

[[nodiscard]] constexpr bool sort_by_definition_id(const benchmark_image_data& data, const uint64_t def_id) noexcept
{
	return data.id < def_id;
}

[[nodiscard]] image_size image_size_from_def(const definition& def) noexcept
{
	constexpr std::uint16_t small_side{64U};
	constexpr std::uint16_t large_side{1024U};
	const auto size = def.size;
	return {
			.width = size == size_gen_t::small || size == size_gen_t::tall ? small_side : large_side,
			.height = size == size_gen_t::small || size == size_gen_t::wide ? small_side : large_side
	};
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
	std::uint64_t value_index{0U};
	const auto channels_value = static_cast<std::uint64_t>(channels);
	for (; data_ptr != data_end; ++data_ptr, ++value_index)
	{
		*data_ptr = static_cast<std::uint8_t>(value_index % byte_modulo[value_index % channels_value]);
	}
}

void set_random_image(
		std::uint8_t* IMFY_RESTRICT data_ptr, const std::uint8_t* IMFY_RESTRICT data_end, const std::uint64_t seed
)
{
	std::mt19937 prng{static_cast<std::uint32_t>(seed)};
	// uint8_t is explicitly excluded by the standard, see https://eel.is/c++draft/rand.req.genl#1.6.
	std::uniform_int_distribution<std::uint16_t> uniform_dist{0U, std::numeric_limits<std::uint8_t>::max()};
	for (; data_ptr != data_end; ++data_ptr)
	{
		*data_ptr = static_cast<std::uint8_t>(uniform_dist(prng));
	}
}

raw_image generate_image(const definition& def, const image_size& size, const std::uint64_t def_id)
{
	raw_image image{def.channels, def.bit_depth, size};
	auto* IMFY_RESTRICT data_ptr = image.data().as_writable_bytes().data();
	const auto* IMFY_RESTRICT data_end = data_ptr + image.data().size_bytes();
	switch (def.image_gen)
	{
		case image_gen_t::zero:
			set_zero_image(data_ptr, data_end);
			break;
		case image_gen_t::modulo:
			set_modulo_image(data_ptr, data_end, def.channels);
			break;
		case image_gen_t::random:
		{
			// Generate the same image for each combination of input parameters.
			set_random_image(data_ptr, data_end, def_id);
			break;
		}
	}

	return image;
}

}

namespace imfy::bench
{

tl::expected<vector<benchmark_image_data>, string> generate_benchmark_images(
		const std::span<const definition> definitions, const std::optional<fs::path_view>& path
)
{
	vector<benchmark_image_data> data{};

	for (const auto& def : definitions)
	{
		const auto def_id = id_from_def(def);
		const auto images_end = data.end();
		const auto position_it = std::lower_bound(data.begin(), images_end, def_id, sort_by_definition_id);
		if (position_it != images_end)
		{
			IMFY_ASSERT(position_it->id == def_id);
			continue;
		}

		const auto size = image_size_from_def(def);
		const auto image_it =
				data.emplace(position_it, benchmark_image_data{.id = def_id, .image = generate_image(def, size, def_id)});

		if (!path.has_value())
		{
			continue;
		}

		const string file_name{fmt::format(
				"imfy_{:d}_{:d}_{:s}_{:d}_{:d}.png", static_cast<int>(def.channels), static_cast<int>(def.bit_depth),
				image_gen_string(def.image_gen), size.width, size.height
		)};

		const auto& image = image_it->image;
		const auto encoded = png::encode(image, compression_t::standard);

		if (!encoded.has_value()) [[unlikely]]
		{
			return tl::unexpected{string{encoded.error()}};
		}

		const auto span{encoded.value().span()};
		if (const auto save_result = fs::save_file(path.value(), file_name, span); !save_result.has_value())
		{
			const auto description = fs::error_description(save_result.error());
			return tl::make_unexpected(fmt::format("Could not save file {:s}: {:s}", file_name, description));
		}
	}

	return data;
}

const raw_image& get_image(const definition& def, const vector<benchmark_image_data>& data) noexcept
{
	const auto def_id = id_from_def(def);
	const auto images_end = data.end();
	const auto position_it = std::lower_bound(data.begin(), images_end, def_id, sort_by_definition_id);
	IMFY_ASSERT(position_it != images_end);
	return position_it->image;
}

}
