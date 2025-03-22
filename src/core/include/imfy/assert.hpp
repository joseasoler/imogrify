/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#ifndef NDEBUG
#include <cassert>
#endif

#if defined(IMOGRIFY_CLANG_TIDY)
#define IMFY_IMPL_ATTR_ASSUME(expression)
#elif IMOGRIFY_COMPILER_MSVC
#define IMFY_IMPL_ATTR_ASSUME(expression) __assume(expression)
#elif IMOGRIFY_COMPILER_GCC
#define IMFY_IMPL_ATTR_ASSUME(expression) __attribute__((assume(expression)))
#elif IMOGRIFY_COMPILER_APPLE_CLANG || IMOGRIFY_COMPILER_CLANG
#define IMFY_IMPL_ATTR_ASSUME(expression) __builtin_assume(expression)
#else
#define IMFY_IMPL_ATTR_ASSUME(expression)
#endif

#if defined(IMOGRIFY_CLANG_TIDY) || defined(NDEBUG)
#define IMFY_ASSERT(expression) ((void)0)
#else
#define IMFY_ASSERT(expression) assert(expression)
#endif

// IMFY_ASSUME. Informs the compiler that an expression will always evaluate to true. Assert on debug builds.
#define IMFY_ASSUME(expression) \
	IMFY_ASSERT(expression);      \
	IMFY_IMPL_ATTR_ASSUME(expression)
