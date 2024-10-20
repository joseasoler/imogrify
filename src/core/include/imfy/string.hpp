/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#include <imfy/allocator.hpp>

#include <string>

namespace imfy
{

/** std::string with the allocator defined for imogrify. */
using string = std::basic_string<char, std::char_traits<char>, allocator<char>>;

} // namespace imfy