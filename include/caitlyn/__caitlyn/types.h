/**
 * This file is part of the Caitlyn library
 * Copyright (C) 2024 Alexander Szawrowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CAITLYN_TYPES_H_
#define CAITLYN_TYPES_H_

#include "caitlyn/__caitlyn/config.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

using __char_t = decltype('\0');
using __wide_char_t = decltype(L'\0');
#if __CAITLYN_HAS_CXX20
using __utf8_char_t = decltype(u8'\0');
#else
using __utf8_char_t = __char_t;
#endif
using __utf16_char_t = decltype(u'\0');
using __utf32_char_t = decltype(U'\0');

using __signed_char_t = signed char;
using __unsigned_char_t = unsigned char;
using __signed_short_int = signed short int;
using __unsigned_short_int = unsigned short int;
using __signed_int_t = decltype(0);
using __unsigned_int_t = decltype(0U);
using __signed_long_type = decltype(0L);
using __unsigned_long_t = decltype(0UL);
using __signed_long_long_t = decltype(0LL);
using __unsigned_long_long_t = decltype(0ULL);

using __int8_t  = __signed_char_t;
using __uint8_t  = __unsigned_char_t;
using __int16_t  = __signed_short_int;
using __uint16_t  = __unsigned_short_int;
using __int32_t  = __signed_int_t;
using __uint32_t  = __unsigned_int_t;
#if defined(__CAITLYN_OS_UNIX) && (__CAITLYN_WORDSIZE == 64)
using __int64_t = __signed_long_type;
using __uint64_t = __unsigned_long_t;
using __intmax_t = __signed_long_type;
using __uintmax_t = __unsigned_long_t;
using __intptr_t = __signed_long_type;
using __uintptr_t = __unsigned_long_t;
#else
using __int64_t = __signed_long_long_t;
using __uint64_t = __unsigned_long_long_t;
using __intmax_t = __signed_long_long_t;
using __uintmax_t = __unsigned_long_long_t;
using __intptr_t = __signed_long_long_t;
using __uintptr_t = __unsigned_long_long_t;
#endif

using __float32_t = decltype(.0f);
using __float64_t = decltype(.0);
using __float_n_t = decltype(.0L);

using __difference_type_t =
    decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

using __signed_size_t = __difference_type_t;
using __unsigned_size_t = decltype(sizeof(0));

using __boolean_t = decltype(false);
using __null_pointer_t = decltype(nullptr);

__CAITLYN_DETAIL_NAMESPACE_END

// Character
using char_t = __detail::__char_t;
using schar_t = __detail::__signed_char_t;
using uchar_t = __detail::__unsigned_char_t;
using xchar_t = __detail::__wide_char_t;
using u8char_t = __detail::__utf8_char_t;
using u16char_t = __detail::__utf16_char_t;
using u32char_t = __detail::__utf32_char_t;

// Integer
using sbyte_t = __detail::__int8_t;
using byte_t = __detail::__uint8_t;
using int8_t = __detail::__int8_t;
using uint8_t = __detail::__uint8_t;
using int16_t = __detail::__int16_t;
using uint16_t = __detail::__uint16_t;
using int32_t = __detail::__int32_t;
using uint32_t = __detail::__uint32_t;
using int64_t = __detail::__int64_t;
using uint64_t = __detail::__uint64_t;

using int_t = __detail::__signed_int_t;
using uint_t = __detail::__unsigned_int_t;
using intmax_t = __detail::__intmax_t;
using uintmax_t = __detail::__uintmax_t;
using intptr_t = __detail::__intptr_t;
using uintptr_t = __detail::__uintptr_t;
using ssize_t = __detail::__signed_size_t;
using size_t = __detail::__unsigned_size_t;
using ptrdiff_t = __detail::__difference_type_t;

// Floating point
using float32_t = __detail::__float32_t;
using float64_t = __detail::__float64_t;
using floatx_t = __detail::__float_n_t;

// System
using bool_t = __detail::__boolean_t;
using nullptr_t = __detail::__null_pointer_t;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_TYPES_H_
