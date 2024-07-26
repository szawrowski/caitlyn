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
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename T>
struct MakeSignedType
{
};

template <>
struct MakeSignedType<char>
{
    using Type = signed char;
};

template <>
struct MakeSignedType<unsigned char>
{
    using Type = signed char;
};

template <>
struct MakeSignedType<unsigned short>
{
    using Type = short;
};

template <>
struct MakeSignedType<unsigned int>
{
    using Type = int;
};

template <>
struct MakeSignedType<unsigned long>
{
    using Type = long;
};

template <>
struct MakeSignedType<unsigned long long>
{
    using Type = long long;
};

template <>
struct MakeSignedType<signed char>
{
    using Type = signed char;
};

template <>
struct MakeSignedType<short>
{
    using Type = short;
};

template <>
struct MakeSignedType<int>
{
    using Type = int;
};

template <>
struct MakeSignedType<long>
{
    using Type = long;
};

template <>
struct MakeSignedType<long long>
{
    using Type = long long;
};

template <typename T>
struct MakeUnsignedType
{
};

template <>
struct MakeUnsignedType<char>
{
    using Type = unsigned char;
};

template <>
struct MakeUnsignedType<signed char>
{
    using Type = unsigned char;
};

template <>
struct MakeUnsignedType<short>
{
    using Type = unsigned short;
};

template <>
struct MakeUnsignedType<int>
{
    using Type = unsigned int;
};

template <>
struct MakeUnsignedType<long>
{
    using Type = unsigned long;
};

template <>
struct MakeUnsignedType<long long>
{
    using Type = unsigned long long;
};

template <>
struct MakeUnsignedType<unsigned char>
{
    using Type = unsigned char;
};

template <>
struct MakeUnsignedType<unsigned short>
{
    using Type = unsigned short;
};

template <>
struct MakeUnsignedType<unsigned int>
{
    using Type = unsigned int;
};

template <>
struct MakeUnsignedType<unsigned long>
{
    using Type = unsigned long;
};

template <>
struct MakeUnsignedType<unsigned long long>
{
    using Type = unsigned long long;
};

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
using MakeSigned = traits::MakeSignedType<T>;

template <typename T>
using MakeUnsigned = traits::MakeUnsignedType<T>;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_SIGN_MODIFIERS_H_
