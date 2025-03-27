/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <tl/expected.hpp>

#include <filesystem>
#include <span>

namespace imfy::bench
{

class benchmark_image_data final
{
public:
	explicit benchmark_image_data(const definition& def, image::image_size img_size);

	image_gen_t image_gen_;
	image::raw_image image_;
	string filename_;
};

class benchmark_images final
{
public:
	explicit benchmark_images(std::span<const definition> definitions);

	benchmark_images(const benchmark_images&) = default;
	benchmark_images(benchmark_images&&) noexcept = default;
	benchmark_images& operator=(const benchmark_images&) = default;
	benchmark_images& operator=(benchmark_images&&) noexcept = default;
	~benchmark_images() = default;

	/**
	 * Save generated reference images to the filesystem.
	 * @param path Destination path folder.
	 * @return True unless an error happened.
	 */
	[[nodiscard]] bool save(const std::filesystem::path& path) const;

	/**
	 * Obtains an input image from the set.
	 * @param def Definition to test. Must be one of the definitions used to initialize the images.
	 * @return Referenced input image or an error description.
	 */
	[[nodiscard]] const image::raw_image& get(const definition& def) const noexcept;

private:
	vector<benchmark_image_data> images_;
};

}
