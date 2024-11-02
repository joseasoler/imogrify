/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#include <tl/expected.hpp>

#include <string_view>

#include "imfy/runtime.hpp"

namespace imfy::runtime
{

tl::expected<cpu_info, std::string_view> cpu_information()
{
	return {};
}

} // namespace imfy::runtime
