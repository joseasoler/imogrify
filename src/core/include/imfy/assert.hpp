/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

#ifndef NDEBUG
#if IMOGRIFY_USE_LIBASSERT
#include <libassert/assert.hpp>
#else
#include <cassert>
#endif
#endif

// IMFY_ASSUME. Informs the compiler that an expression will always evaluate to true. Assert on debug builds.
#if defined(IMOGRIFY_CLANG_TIDY)
// Prevent clang-tidy from issuing warnings coming from libassert code.
#define IMFY_ASSUME(expression)
#elif !defined(NDEBUG)
#if IMOGRIFY_USE_LIBASSERT
#define IMFY_ASSUME(...) ASSUME(__VA_ARGS__)
#else
#define IMFY_ASSUME(...) assert(__VA_ARGS__)
#endif
#elif IMOGRIFY_COMPILER_MSVC
#define IMFY_ASSUME(expression) __assume(expression)
#elif IMOGRIFY_COMPILER_GCC
#define IMFY_ASSUME(expression) __attribute__((assume(expression)))
#elif IMOGRIFY_COMPILER_APPLE_CLANG || IMOGRIFY_COMPILER_CLANG
#define IMFY_ASSUME(expression) __builtin_assume(expression)
#else
#define IMFY_ASSUME(expression)
#endif

#if defined(IMOGRIFY_CLANG_TIDY) || defined(NDEBUG)
#define IMFY_ASSERT(expression)
#elif IMOGRIFY_USE_LIBASSERT
#define IMFY_ASSERT(...) DEBUG_ASSERT(__VA_ARGS__)
#else
#define IMFY_ASSERT(...) assert(__VA_ARGS__)
#endif
