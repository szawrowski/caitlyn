// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_BASIC_TYPES_H_
#define CAITLYN_CORE_DEFS_BASIC_TYPES_H_

#include "caitlyn/core/defs/core_definitions.h"
#include "caitlyn/core/defs/global_definitions.h"

BEGIN_CAITLYN_NS

// Characters
using stdchar_t = char;
using uchar_t = unsigned char;
using schar_t = signed char;
using xchar_t = wchar_t;
using u8char_t = char;
using u16char_t = char16_t;
using u32char_t = char32_t;

// Integrals
using byte_t = unsigned char;
using int_t = signed int;
using uint_t = unsigned int;
using int8_t = signed char;
using uint8_t = unsigned char;
using int16_t = signed short int;
using uint16_t = unsigned short int;
using int32_t = signed int;
using uint32_t = unsigned int;
#if defined(__caitlyn_unix) && (__caitlyn_arch == 64)
  using int64_t = signed long int;
  using uint64_t = unsigned long int;
#else
  using int64_t = signed long long int;
  using uint64_t = unsigned long long int;
#endif

using ptrdiff_t =
    decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

using size_t = decltype(sizeof(0));
using ssize_t = ptrdiff_t;

// Floating point
using float32_t = float;
using float64_t = double;
using floatx_t = long double;

// Logical
using bool_t = bool;

// System
using null_t = decltype(nullptr);

END_CAITLYN_NS

#endif  // CAITLYN_CORE_DEFS_BASIC_TYPES_H_
