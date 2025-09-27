/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

// NOLINTBEGIN(*-macro-usage)

#if defined(NDEBUG) || defined(IMOGRIFY_CLANG_TIDY_ANALYSIS)
#define IMFY_ASSERT(...) ((void)0)
#elif IMOGRIFY_USE_LIBASSERT

#include <libassert/assert.hpp>
#define IMFY_ASSERT(expression, ...) LIBASSERT_INVOKE(expression, "IMFY_ASSERT", debug_assertion, LIBASSERT_NOP_ACTION, __VA_ARGS__)
#else
#include <cassert>

#define IMFY_ASSERT(expression, ...) assert(expression)
#endif

#if defined(IMOGRIFY_CLANG_TIDY_ANALYSIS)
#define IMFY_ASSUME(expression, ...) ((void)0)
#elif !defined(NDEBUG)
#define IMFY_ASSUME(expression, ...) IMFY_ASSERT(expression, __VA_ARGS__)
#elif IMOGRIFY_COMPILER_MSVC
#define IMFY_ASSUME(expression, ...) __assume(expression)
#elif IMOGRIFY_COMPILER_GCC
#define IMFY_ASSUME(expressio, ...n) __attribute__((assume(expression)))
#elif IMOGRIFY_COMPILER_CLANG
#define IMFY_ASSUME(expression, ...) __builtin_assume(expression)
#else
#define IMFY_ASSUME(expression, ...) ((void)0)
#endif

// NOLINTEND(*-macro-usage)
