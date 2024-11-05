/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/vector.hpp>

#include <span>
#include <string_view>

namespace imfy::bench
{

class benchmark_images final
{
public:
	explicit benchmark_images(std::span<const definition> definitions, std::string_view path);

	benchmark_images(const benchmark_images&) = default;
	benchmark_images(benchmark_images&&) noexcept = default;
	benchmark_images& operator=(const benchmark_images&) = default;
	benchmark_images& operator=(benchmark_images&&) noexcept = default;
	~benchmark_images() = default;

	/**
	 * Obtains an input image from the set.
	 * @param channels Channels of the image.
	 * @param bit_depth Bit depth of the image.
	 * @param size Width and height of the image.
	 * @return Referenced input image, or nullptr if it does not exist (which means a bug in the benchmark code).
	 */
	[[nodiscard]] const raw_image* get(std::uint8_t channels, std::uint8_t bit_depth, size_def size) const noexcept;

private:
	vector<raw_image> images_;
};

} // namespace imfy::bench
