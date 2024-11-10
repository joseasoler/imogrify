/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/benchmark_output.hpp"

#include <imfy/benchmark_parameters.hpp>
#include <imfy/benchmark_result.hpp>
#include <imfy/image_format.hpp>

#include <magic_enum.hpp>

#include <cstdint>
#include <filesystem>
#include <iostream>
#include <limits>
#include <memory>
#include <span>
#include <string_view>
#include <utility>

#include "imfy/markdown.hpp"

#include <nanobench.h>

namespace
{
using namespace imfy::bench;
using namespace imfy::image;

using namespace std::string_view_literals;

constexpr auto library_header = "Library"sv;
constexpr auto channels_header = "Channels"sv;
constexpr auto bit_depth_header = "Bits"sv;
constexpr auto image_gen_header = "Gen"sv;

constexpr auto width_header = "Width"sv;
constexpr auto height_header = "Height"sv;

constexpr auto file_size_header = "Size (KiB)"sv;
constexpr auto file_size_rel_header = "Size(%)"sv;
constexpr auto speed_header = "Mpix/s"sv;
constexpr auto relative_speed_header = "Spd(%)"sv;
constexpr auto error_speed_header = "Err(%)"sv;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
constexpr auto instructions_header = "Inst."sv;
constexpr auto cycles_header = "Cycles"sv;
constexpr auto branches_header = "Branches"sv;
constexpr auto branch_misses_header = "B. misses"sv;
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)

std::string_view channel_string(format_def format, channel_t channels)
{
	if (format == format_def::png)
	{
		switch (channels)
		{
			case channel_t::one:
				return "g";
			case channel_t::two:
				return "ga";
			case channel_t::three:
				return "rgb";
			default:
			case channel_t::four:
				return "rgba";
		}
	}
	return "";
}

} // namespace

namespace imfy::bench
{

class benchmark_renderer
{
public:
	explicit benchmark_renderer(std::filesystem::path path)
		: path_{std::move(path)}
	{
	}
	benchmark_renderer(const benchmark_renderer&) = delete;
	benchmark_renderer(benchmark_renderer&&) noexcept = default;
	benchmark_renderer& operator=(const benchmark_renderer&) = delete;
	benchmark_renderer& operator=(benchmark_renderer&&) noexcept = default;
	virtual ~benchmark_renderer() = default;

	virtual void render_context() = 0;
	virtual void render(const result& res) = 0;

	[[nodiscard]] const std::filesystem::path& path() const noexcept { return path_; }

private:
	std::filesystem::path path_;
};

class markdown_renderer final : public benchmark_renderer
{
public:
	explicit markdown_renderer(std::filesystem::path path)
		: benchmark_renderer(std::move(path))
		, current_format_{invalid_format}
		, current_operation_{invalid_operation}
		, mark_{std::cout}
	{
	}

	void render_context() override
	{
		mark_.add_heading(markdown::heading::level_1, "Library microbenchmarks");

		mark_.add_build_information(markdown::heading::level_2);
		mark_.add_runtime_information(markdown::heading::level_2);

		mark_.add_heading(markdown::heading::level_2, "Microbenchmarks");
	}

	void render(const result& res) override
	{
		// Update headers if needed.
		if (res.format != current_format_)
		{
			current_format_ = res.format;
			current_operation_ = res.operation;
			mark_.add_heading(markdown::heading::level_3, magic_enum::enum_name(current_format_));
			mark_.add_heading(markdown::heading::level_4, magic_enum::enum_name(current_operation_));
		}
		else if (res.operation != current_operation_)
		{
			current_operation_ = res.operation;
			mark_.add_heading(markdown::heading::level_4, magic_enum::enum_name(current_operation_));
		}

		markdown_table table;
		table.add_cell_str(library_header);
		table.add_cell_str(channels_header);
		table.add_cell_str(bit_depth_header);
		table.add_cell_str(image_gen_header);
		table.add_cell_str(width_header);
		table.add_cell_str(height_header);
		table.add_cell_str(file_size_header);
		table.add_cell_str(file_size_rel_header);
		table.add_cell_str(speed_header);
		table.add_cell_str(relative_speed_header);
		table.add_cell_str(error_speed_header);
#if ANKERL_NANOBENCH(PERF_COUNTERS)
		table.add_cell_str(instructions_header);
		table.add_cell_str(cycles_header);
		table.add_cell_str(branches_header);
		table.add_cell_str(branch_misses_header);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
		table.end_row();

		for (const auto& lib_res : res.library_results)
		{
			table.add_cell_str(magic_enum::enum_name(lib_res.library));
			table.add_cell_str(channel_string(res.format, res.channels));
			table.add_cell_uint(static_cast<std::uint64_t>(res.bit_depth));
			table.add_cell_str(magic_enum::enum_name(res.image_gen));
			table.add_cell_uint(res.img_size.width);
			table.add_cell_uint(res.img_size.height);
			table.add_cell_double(lib_res.file_size, " KiB");
			table.add_cell_double(lib_res.file_size_rel, "%");
			table.add_cell_double(lib_res.mpix_second, " Mpix/s");
			table.add_cell_double(lib_res.speed_relative, "%");
			table.add_cell_double(lib_res.speed_error, "%");
#if ANKERL_NANOBENCH(PERF_COUNTERS)
			table.add_cell_uint(lib_res.instructions);
			table.add_cell_uint(lib_res.cycles);
			table.add_cell_uint(lib_res.branch_instructions);
			table.add_cell_uint(lib_res.branch_misses);
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
			table.end_row();
		}

		mark_.add_table(table);
	}

private:
	static constexpr auto invalid_format = static_cast<format_def>(std::numeric_limits<std::uint8_t>::max());
	static constexpr auto invalid_operation = static_cast<operation_def>(std::numeric_limits<std::uint8_t>::max());

	format_def current_format_;
	operation_def current_operation_;
	markdown mark_;
};

class csv_renderer final : public benchmark_renderer
{
public:
	static constexpr char sep = ',';

	explicit csv_renderer(std::filesystem::path path)
		: benchmark_renderer(std::move(path))
	{
	}

	void render_context() override
	{
		std::cout << library_header << sep << channels_header << sep << bit_depth_header << sep << width_header << sep
							<< height_header << sep << file_size_rel_header << sep << speed_header << sep << relative_speed_header
							<< sep << error_speed_header;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
		std::cout << sep << instructions_header << sep << cycles_header << sep << branches_header << sep
							<< branch_misses_header;
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
		std::cout << '\n';
	}
	void render(const result& res) override
	{
		for (const auto& lib_res : res.library_results)
		{
			std::cout << magic_enum::enum_name(lib_res.library) << sep << channel_string(res.format, res.channels) << sep
								<< static_cast<int>(res.bit_depth) << sep << res.img_size.width << sep << res.img_size.height << sep
								<< lib_res.file_size_rel << sep << lib_res.mpix_second << sep << lib_res.speed_relative << sep
								<< lib_res.speed_error;
#if ANKERL_NANOBENCH(PERF_COUNTERS)
			std::cout << lib_res.instructions << sep << lib_res.cycles << sep << lib_res.branch_instructions << sep
								<< lib_res.branch_misses;
#endif // ANKERL_NANOBENCH(PERF_COUNTERS)
			std::cout << '\n';
		}
	}
};

benchmark_output::benchmark_output(const std::filesystem::path& path, std::span<const renderer> renderers)
{
	for (const renderer renderer_def : renderers)
	{
		switch (renderer_def)
		{
			case renderer::markdown:
				renderers_.emplace_back(std::make_unique<markdown_renderer>(path));
				break;
			case renderer::csv:
				renderers_.emplace_back(std::make_unique<csv_renderer>(path));
				break;
		}
		renderers_.back()->render_context();
	}
}

benchmark_output::~benchmark_output() = default;

void benchmark_output::output(const result& result)
{
	for (const auto& renderer : renderers_)
	{
		renderer->render(result);
	}
}

} // namespace imfy::bench