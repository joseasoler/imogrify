/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

#include <filesystem>
#include <optional>
#include <span>

namespace imfy::bench
{

struct benchmark_image_data final
{
	size_t id;
	image::raw_image image;
};

/**
 * Generates images required for the provided definitions.
 * @param definitions Definitions to be benchmarked.
 * @param path If present, generated images will be saved to the filesystem as PNG.
 * @return Benchmark image data.
 */

tl::expected<vector<benchmark_image_data>, string> generate_benchmark_images(
		std::span<const definition> definitions, const std::optional<std::filesystem::path>& path
);

/**
 * Obtains an input image from the set.
 * @param def Definition to test. Must be one of the definitions used to initialize the images.
 * @param data Generated benchmark image data.
 * @return Referenced input image.
 */
[[nodiscard]] const image::raw_image& get_image(
		const definition& def, const vector<benchmark_image_data>& data
) noexcept;

}
