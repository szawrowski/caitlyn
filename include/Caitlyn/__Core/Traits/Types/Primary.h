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

#ifndef CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_
#define CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_

#include "Caitlyn/__Core/Traits/Types/Relationships.h"
#include "Caitlyn/__Core/Traits/Types/Specifiers.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <class T>
struct IsVoidType : IsSameType<void, RemoveCV<T>>::Type
{
};

template <class T>
struct IsNullPointerType : IsSameType<std::nullptr_t, RemoveCV<T>>::Type
{
};

template <class T>
struct IsBooleanType : IsSameType<bool, RemoveCV<T>>::Type
{
};

// Characters
template <typename, typename = void>
struct IsCharacterType : FalseType
{
};

template <>
struct IsCharacterType<char> : TrueType
{
};

template <>
struct IsCharacterType<signed char> : TrueType
{
};

template <>
struct IsCharacterType<unsigned char> : TrueType
{
};

template <>
struct IsCharacterType<wchar_t> : TrueType
{
};

#if __CAITLYN_HAS_CXX20
template <>
struct IsCharacterType<char8_t> : TrueType
{
};
#endif

template <>
struct IsCharacterType<char16_t> : TrueType
{
};

template <>
struct IsCharacterType<char32_t> : TrueType
{
};

// Integers
template <typename, typename = void>
struct IsIntegerType : FalseType
{
};

template <>
struct IsIntegerType<signed char> : TrueType
{
};

template <>
struct IsIntegerType<unsigned char> : TrueType
{
};

template <>
struct IsIntegerType<short> : TrueType
{
};

template <>
struct IsIntegerType<unsigned short> : TrueType
{
};

template <>
struct IsIntegerType<int> : TrueType
{
};

template <>
struct IsIntegerType<unsigned> : TrueType
{
};

template <>
struct IsIntegerType<long> : TrueType
{
};

template <>
struct IsIntegerType<unsigned long> : TrueType
{
};

template <>
struct IsIntegerType<long long> : TrueType
{
};

template <>
struct IsIntegerType<unsigned long long> : TrueType
{
};

// Floating point
template <typename, typename = void>
struct IsFloatingType : FalseType
{
};

template <>
struct IsFloatingType<float> : TrueType
{
};

template <>
struct IsFloatingType<double> : TrueType
{
};

template <>
struct IsFloatingType<long double> : TrueType
{
};

template <class T>
struct IsArrayType : FalseType
{
};

template <class T>
struct IsArrayType<T[]> : TrueType
{
};

template <class T, std::size_t N>
struct IsArrayType<T[N]> : TrueType
{
};

template <class T>
struct IsPointerType : FalseType
{
};

template <class T>
struct IsPointerType<T*> : TrueType
{
};

template <class T>
struct IsPointerType<T* const> : TrueType
{
};

template <class T>
struct IsPointerType<T* volatile> : TrueType
{
};

template <class T>
struct IsPointerType<T* const volatile> : TrueType
{
};

template <typename T>
struct IsLValueReferenceType : FalseType
{
};

template <typename T>
struct IsLValueReferenceType<T&> : TrueType
{
};

template <typename T>
struct IsRValueReferenceType : FalseType
{
};

template <typename T>
struct IsRValueReferenceType<T&&> : TrueType
{
};

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_
