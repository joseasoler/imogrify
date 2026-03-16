/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
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
