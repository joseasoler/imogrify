/*
 * This Source Code Form is subject to the terms of the Mozilla Public License, v. 2.0. If a copy of the MPL was not
 * distributed with this file, You can obtain one at https://mozilla.org/MPL/2.0/.
 */

#pragma once

// IMFY_ALWAYS_INLINE: Forces the specified function to be online. Used only on very specific cases.
#if IMOGRIFY_COMPILER_MSVC
#define IMFY_ALWAYS_INLINE __forceinline
#else
#define IMFY_ALWAYS_INLINE inline __attribute__((always_inline))
#endif

// IMFY_ASSUME:Informs the compiler that an expression will always evaluate to true.
#if IMOGRIFY_COMPILER_MSVC
#define IMFY_ASSUME(expression) __assume(expression)
#elif IMOGRIFY_COMPILER_GCC && !defined(IMOGRIFY_CLANG_TIDY)
#define IMFY_ASSUME(expression) __attribute__((assume(expression)))
#elif IMOGRIFY_COMPILER_APPLE_CLANG || IMOGRIFY_COMPILER_CLANG
#define IMFY_ASSUME(expression) __builtin_assume(expression)
#else
#define IMFY_ASSUME(expression)
#endif

// IMFY_RESTRICT: For the lifetime of a pointer, no other pointer will be access the object to which it points.
#if IMOGRIFY_COMPILER_MSVC
#define IMFY_RESTRICT __restrict
#else
#define IMFY_RESTRICT __restrict__
#endif
