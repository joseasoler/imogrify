/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include "imfy/runtime.hpp"

#include <array>

#include "cpu_features_macros.h"

#if defined(CPU_FEATURES_ARCH_AARCH64)
#include "cpuinfo_aarch64.h"
#elif defined(CPU_FEATURES_ARCH_ARM)
#include "cpuinfo_arm.h"
#elif defined(CPU_FEATURES_ARCH_LOONGARCH)
#include "cpuinfo_loongarch.h"
#elif defined(CPU_FEATURES_ARCH_MIPS)
#include "cpuinfo_mips.h"
#elif defined(CPU_FEATURES_ARCH_PPC)
#include "cpuinfo_ppc.h"
#elif defined(CPU_FEATURES_ARCH_RISCV)
#include "cpuinfo_riscv.h"
#elif defined(CPU_FEATURES_ARCH_S390X)
#include "cpuinfo_s390x.h"
#elif defined(CPU_FEATURES_ARCH_X86)
#include "cpuinfo_x86.h"
#endif

namespace
{

using namespace cpu_features;

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFINE_PLATFORM_ALIASES_CONCATENATION(PlatformId)                             \
	constexpr auto get_cpu_info = Get##PlatformId##Info;                                \
	constexpr auto get_microarchitecture = Get##PlatformId##Microarchitecture;          \
	constexpr auto get_microarchitecture_name = Get##PlatformId##MicroarchitectureName; \
	using cpu_feature_id = PlatformId##FeaturesEnum;                                    \
	constexpr auto has_cpu_feature = Get##PlatformId##FeaturesEnumValue;                \
	constexpr auto get_feature_name = Get##PlatformId##FeaturesEnumName

// NOLINTNEXTLINE(cppcoreguidelines-macro-usage)
#define DEFINE_PLATFORM_ALIASES(PlatformId) DEFINE_PLATFORM_ALIASES_CONCATENATION(PlatformId)

// Each platform must define its aliases and a list of feature ids to report.
// Untested platforms have an empty list of feature ids.
#if defined(CPU_FEATURES_ARCH_AARCH64)

DEFINE_PLATFORM_ALIASES(Aarch64);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_ARM)

DEFINE_PLATFORM_ALIASES(Arm);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_LOONGARCH)

DEFINE_PLATFORM_ALIASES(LoongArch);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_MIPS)

DEFINE_PLATFORM_ALIASES(Mips);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_PPC)

DEFINE_PLATFORM_ALIASES(PPC);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_RISCV)

DEFINE_PLATFORM_ALIASES(Riscv);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_S390X)

DEFINE_PLATFORM_ALIASES(S390X);
constexpr std::array<cpu_feature_id, 0U> cpu_feature_ids{};

#elif defined(CPU_FEATURES_ARCH_X86)

DEFINE_PLATFORM_ALIASES(X86);
constexpr std::array cpu_feature_ids{X86_SSE,		 X86_SSE2,	X86_SSE3, X86_SSSE3,		X86_SSE4_1,
																		 X86_SSE4_2, X86_SSE4A, X86_AVX,	X86_AVX_VNNI, X86_AVX2};

#endif

} // namespace

namespace imfy::runtime
{

cpu_info cpu_information()
{
	const auto raw_cpu_info = get_cpu_info();
	cpu_info output_cpu_info{};

	// Remove trailing spaces from the CPU brand string.
	output_cpu_info.brand = static_cast<const char*>(raw_cpu_info.brand_string);
	auto last_index = output_cpu_info.brand.find_last_not_of(' ');
	output_cpu_info.brand.resize(last_index + 1U);

	output_cpu_info.microarchitecture = get_microarchitecture_name(get_microarchitecture(&raw_cpu_info));

	for (const auto& cpu_feature_id : cpu_feature_ids)
	{
		if (has_cpu_feature(&raw_cpu_info.features, cpu_feature_id) != 0)
		{
			output_cpu_info.features.emplace_back(get_feature_name(cpu_feature_id));
		}
	}

	return output_cpu_info;
}

} // namespace imfy::runtime
