/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#if IMOGRIFY_COMPILER_GCC
// On release builds, GCC reports null dereference errors that are covered by assert macros.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wnull-dereference"
#endif

#include <concurrentqueue/moodycamel/concurrentqueue.h>

#if IMOGRIFY_COMPILER_GCC
#pragma GCC diagnostic pop
#endif
