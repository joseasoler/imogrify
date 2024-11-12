/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/benchmark_definition.hpp>
#include <imfy/filesystem.hpp>
#include <imfy/image_size.hpp>
#include <imfy/raw_image.hpp>
#include <imfy/string.hpp>
#include <imfy/vector.hpp>

#include <filesystem>
#include <span>

namespace imfy::bench
{

class benchmark_image_data final
{
public:
	explicit benchmark_image_data(const imfy::bench::definition& def, image::image_size img_size);

	bench::image_gen_t image_gen_;
	image::raw_image image_;
	imfy::string filename_;
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
	 * Save all created reference images to a specific path.
	 * @param path Assumed to be a valid directory.
	 * @return True if saving all images succeeded.
	 */
	[[nodiscard]] bool save_all(const std::filesystem::path& path) const;

	/**
	 * Obtains an input image from the set.
	 * @param def Test definition.
	 * @return Referenced input image, or nullptr if it does not exist (which means a bug in the benchmark code).
	 */
	[[nodiscard]] const image::raw_image* get(const definition& def) const noexcept;

private:
	vector<benchmark_image_data> images_;
};

} // namespace imfy::bench
