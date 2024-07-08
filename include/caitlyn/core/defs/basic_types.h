// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_BASIC_TYPES_H_
#define CAITLYN_CORE_DEFS_BASIC_TYPES_H_

#include "caitlyn/core/defs/global_definitions.h"

__caitlyn_begin_global_namespace

// Common haracters
using char_t = char;
using uchar_t = unsigned char;
using schar_t = signed char;
using xchar_t = wchar_t;

// Unicode characters
using u8char_t = char_t;
using u16char_t = char16_t;
using u32char_t = char32_t;

// Special integrals
using byte_t = uchar_t;
using int_t = decltype(0);
using uint_t = decltype(0U);

// Common integrals
using int8_t = schar_t;
using uint8_t = uchar_t;
using int16_t = signed short int;
using uint16_t = unsigned short int;
using int32_t = int_t;
using uint32_t = uint_t;
#if defined(__caitlyn_unix) && (__caitlyn_arch == 64)
  using int64_t = decltype(0L);
  using uint64_t = decltype(0UL);
#else
  using int64_t = decltype(0LL);
  using uint64_t = decltype(0ULL);
#endif

// System integrals
using ptrdiff_t =
    decltype(static_cast<int_t*>(nullptr) - static_cast<int_t*>(nullptr));

using size_t = decltype(sizeof(0));
using ssize_t = ptrdiff_t;
using uintmax_t = size_t;
using uintptr_t = size_t;
using streamsize_t = ptrdiff_t;

// Floating point
using float32_t = decltype(.0f);
using float64_t = decltype(.0);
using floatx_t = decltype(.0L);

// Logical
using bool_t = decltype(true);

// System
using null_t = decltype(nullptr);

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_DEFS_BASIC_TYPES_H_
