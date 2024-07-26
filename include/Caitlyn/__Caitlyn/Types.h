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

#include "Caitlyn/__Caitlyn/Config.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

using __char_t = decltype('\0');
using __wide_char_t = decltype(L'\0');
#if __CAITLYN_HAS_CXX20
using __utf8_char_t = decltype(u8 '\0');
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

using __int8_t = __signed_char_t;
using __uint8_t = __unsigned_char_t;
using __int16_t = __signed_short_int;
using __uint16_t = __unsigned_short_int;
using __int32_t = __signed_int_t;
using __uint32_t = __unsigned_int_t;
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

using __difference_type_t = decltype(static_cast<int*>(nullptr) - static_cast<int*>(nullptr));

using __signed_size_t = __difference_type_t;
using __unsigned_size_t = decltype(sizeof(0));

using __boolean_t = decltype(false);
using __null_pointer_t = decltype(nullptr);

__CAITLYN_DETAIL_NAMESPACE_END

// Character
using StdChar = __detail::__char_t;
using WChar = __detail::__wide_char_t;
using Char8 = __detail::__utf8_char_t;
using Char16 = __detail::__utf16_char_t;
using Char32 = __detail::__utf32_char_t;

// Integer
using SByte = __detail::__int8_t;
using Byte = __detail::__uint8_t;
using Int8 = __detail::__int8_t;
using UInt8 = __detail::__uint8_t;
using Int16 = __detail::__int16_t;
using UInt16 = __detail::__uint16_t;
using Int32 = __detail::__int32_t;
using UInt32 = __detail::__uint32_t;
using Int64 = __detail::__int64_t;
using UInt64 = __detail::__uint64_t;

using Int = __detail::__signed_int_t;
using UInt = __detail::__unsigned_int_t;
using IntMax = __detail::__intmax_t;
using UIntMax = __detail::__uintmax_t;
using IntPtr = __detail::__intptr_t;
using UIntPtr = __detail::__uintptr_t;

using SSizeType = __detail::__signed_size_t;
using SizeType = __detail::__unsigned_size_t;
using PtrDiff = __detail::__difference_type_t;

// Floating point
using Float = __detail::__float32_t;
using Double = __detail::__float64_t;
using Decimal = __detail::__float_n_t;

// System
using Bool = __detail::__boolean_t;
using NullPtr = __detail::__null_pointer_t;

using CodePoint = __detail::__uint32_t;

using CharPtr = char*;
using CString = const char*;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif //CAITLYN_TYPES_H_
