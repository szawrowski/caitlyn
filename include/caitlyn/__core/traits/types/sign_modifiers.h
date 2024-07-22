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

#ifndef CAITLUN_CORE_TRAITS_TYPES_SIGN_MODIFIERS_H_
#define CAITLUN_CORE_TRAITS_TYPES_SIGN_MODIFIERS_H_

#include "caitlyn/__base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename T>
struct make_signed_t {};

template <>
struct make_signed_t<char> { using type = signed char; };

template <>
struct make_signed_t<unsigned char> { using type = signed char; };

template <>
struct make_signed_t<unsigned short> { using type = short; };

template <>
struct make_signed_t<unsigned int> { using type = int; };

template <>
struct make_signed_t<unsigned long> { using type = long; };

template <>
struct make_signed_t<unsigned long long> { using type = long long; };

template <>
struct make_signed_t<signed char> { using type = signed char; };

template <>
struct make_signed_t<short> { using type = short; };

template <>
struct make_signed_t<int> { using type = int; };

template <>
struct make_signed_t<long> { using type = long; };

template <>
struct make_signed_t<long long> { using type = long long; };

template <typename T>
struct make_unsigned_t {};

template <>
struct make_unsigned_t<char> { using type = unsigned char; };

template <>
struct make_unsigned_t<signed char> { using type = unsigned char; };

template <>
struct make_unsigned_t<short> { using type = unsigned short; };

template <>
struct make_unsigned_t<int> { using type = unsigned int; };

template <>
struct make_unsigned_t<long> { using type = unsigned long; };

template <>
struct make_unsigned_t<long long> { using type = unsigned long long; };

template <>
struct make_unsigned_t<unsigned char> { using type = unsigned char; };

template <>
struct make_unsigned_t<unsigned short> { using type = unsigned short; };

template <>
struct make_unsigned_t<unsigned int> { using type = unsigned int; };

template <>
struct make_unsigned_t<unsigned long> { using type = unsigned long; };

template <>
struct make_unsigned_t<unsigned long long> { using type = unsigned long long; };

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
using make_signed = traits::make_signed_t<T>;

template <typename T>
using make_unsigned = traits::make_unsigned_t<T>;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_SIGN_MODIFIERS_H_
