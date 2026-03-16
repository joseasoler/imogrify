/*
 * SPDX-FileCopyrightText: 2026 José Ángel Soler Ortiz
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

// NOLINTBEGIN(*-macro-usage)

#if defined(NDEBUG) || defined(IMOGRIFY_CLANG_TIDY_ANALYSIS)
#define IMFY_ASSERT(...) ((void)0)
#elif IMOGRIFY_USE_LIBASSERT

#include <libassert/assert.hpp>
#define IMFY_ASSERT(expression, ...) \
	LIBASSERT_INVOKE(expression, "IMFY_ASSERT", debug_assertion, LIBASSERT_NOP_ACTION, __VA_ARGS__)
#else
#include <cassert>

#define IMFY_ASSERT(expression, ...) assert(expression)
#endif

#ifdef IMOGRIFY_CLANG_TIDY_ANALYSIS
#define IMFY_ASSUME(expression, ...) ((void)0)
#elif !defined(NDEBUG) && IMOGRIFY_USE_LIBASSERT
#define IMFY_ASSUME(expression, ...) \
	LIBASSERT_INVOKE(expression, "IMFY_ASSUME", debug_assertion, LIBASSERT_NOP_ACTION, __VA_ARGS__)
#elif !defined(NDEBUG)
#define IMFY_ASSUME(expression, ...) IMFY_ASSERT(expression, __VA_ARGS__)
#elif IMOGRIFY_COMPILER_MSVC
#define IMFY_ASSUME(expression, ...) __assume(expression)
#elif IMOGRIFY_COMPILER_GCC
#define IMFY_ASSUME(expression, ...) __attribute__((assume(expression)))
#elif IMOGRIFY_COMPILER_CLANG
#define IMFY_ASSUME(expression, ...) \
	if (!(expression)) __builtin_unreachable()
#else
#define IMFY_ASSUME(expression, ...) ((void)0)
#endif

// NOLINTEND(*-macro-usage)
