// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_BASIC_TYPES_H_
#define CAITLYN_CORE_DEFS_BASIC_TYPES_H_

#include "caitlyn/core/defs/core_definitions.h"

namespace cait {

using uchar_t = unsigned char;
using schar_t = signed char;
using u8char_t = char;
using u16char_t = char16_t;
using u32char_t = char32_t;

using int_t = signed int;
using uint_t = unsigned int;

#if defined(__caitlyn_linux) || defined(__caitlyn_apple)
  using int8_t = signed char;
  using uint8_t = unsigned char;
  using int16_t = signed short int;
  using uint16_t = unsigned short int;
  using int32_t = signed int;
  using uint32_t = unsigned int;
  #if defined(__caitlyn_x64)
    using int64_t = signed long int;
    using uint64_t = unsigned long int;
  #else
    using int64_t = signed long long int;
    using uint64_t = unsigned long long int;
  #endif
#elif defined(__caitlyn_windows)
  using int8_t = __int8;
  using uint8_t = unsigned __int8;
  using int16_t = __int16;
  using uint16_t = unsigned __int16;
  using int32_t = __int32;
  using uint32_t = unsigned __int32;
  using int64_t = __int64;
  using uint64_t = unsigned __int64;
#endif

using ptrdiff_t =
    decltype(static_cast<int_t*>(nullptr) - static_cast<int_t*>(nullptr));

using size_t = decltype(sizeof(0));
using ssize_t = ptrdiff_t;

using float32_t = float;
using float64_t = double;
using long_float_t = long double;

using null_t = decltype(nullptr);

}  // namespace cait

#endif  // CAITLYN_CORE_DEFS_BASIC_TYPES_H_
