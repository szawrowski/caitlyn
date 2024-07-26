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

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename>
struct __MakeSigned
{
};

template <>
struct __MakeSigned<char>
{
    using Type = signed char;
};

template <>
struct __MakeSigned<unsigned char>
{
    using Type = signed char;
};

template <>
struct __MakeSigned<unsigned short>
{
    using Type = short;
};

template <>
struct __MakeSigned<unsigned int>
{
    using Type = int;
};

template <>
struct __MakeSigned<unsigned long>
{
    using Type = long;
};

template <>
struct __MakeSigned<unsigned long long>
{
    using Type = long long;
};

template <>
struct __MakeSigned<signed char>
{
    using Type = signed char;
};

template <>
struct __MakeSigned<short>
{
    using Type = short;
};

template <>
struct __MakeSigned<int>
{
    using Type = int;
};

template <>
struct __MakeSigned<long>
{
    using Type = long;
};

template <>
struct __MakeSigned<long long>
{
    using Type = long long;
};

template <typename>
struct __MakeUnsigned
{
};

template <>
struct __MakeUnsigned<char>
{
    using Type = unsigned char;
};

template <>
struct __MakeUnsigned<signed char>
{
    using Type = unsigned char;
};

template <>
struct __MakeUnsigned<short>
{
    using Type = unsigned short;
};

template <>
struct __MakeUnsigned<int>
{
    using Type = unsigned int;
};

template <>
struct __MakeUnsigned<long>
{
    using Type = unsigned long;
};

template <>
struct __MakeUnsigned<long long>
{
    using Type = unsigned long long;
};

template <>
struct __MakeUnsigned<unsigned char>
{
    using Type = unsigned char;
};

template <>
struct __MakeUnsigned<unsigned short>
{
    using Type = unsigned short;
};

template <>
struct __MakeUnsigned<unsigned int>
{
    using Type = unsigned int;
};

template <>
struct __MakeUnsigned<unsigned long>
{
    using Type = unsigned long;
};

template <>
struct __MakeUnsigned<unsigned long long>
{
    using Type = unsigned long long;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using MakeSignedType = typename __Detail::__MakeSigned<T>::Type;

template <typename T>
using MakeUnsignedType = typename __Detail::__MakeUnsigned<T>::Type;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_SIGN_MODIFIERS_H_
