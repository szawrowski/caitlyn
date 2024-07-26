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

template <class T>
struct IsVoidType : IsSameType<void, RemoveCVType<T>>::Type
{
};

template <class T>
struct IsNullPointerType : IsSameType<NullPtr, RemoveCVType<T>>::Type
{
};

template <class T>
struct IsBooleanType : IsSameType<Bool, RemoveCVType<T>>::Type
{
};

__CAITLYN_DETAIL_NAMESPACE_BEGIN

// Characters
template <typename, typename = void>
struct __IsCharacter : FalseType
{
};

template <>
struct __IsCharacter<char> : TrueType
{
};

template <>
struct __IsCharacter<signed char> : TrueType
{
};

template <>
struct __IsCharacter<unsigned char> : TrueType
{
};

template <>
struct __IsCharacter<wchar_t> : TrueType
{
};

#if __CAITLYN_HAS_CXX20
template <>
struct __IsCharacterType<char8_t> : TrueType
{
};
#endif

template <>
struct __IsCharacter<char16_t> : TrueType
{
};

template <>
struct __IsCharacter<char32_t> : TrueType
{
};

// Integers
template <typename, typename = void>
struct __IsInteger : FalseType
{
};

template <>
struct __IsInteger<signed char> : TrueType
{
};

template <>
struct __IsInteger<unsigned char> : TrueType
{
};

template <>
struct __IsInteger<short> : TrueType
{
};

template <>
struct __IsInteger<unsigned short> : TrueType
{
};

template <>
struct __IsInteger<int> : TrueType
{
};

template <>
struct __IsInteger<unsigned> : TrueType
{
};

template <>
struct __IsInteger<long> : TrueType
{
};

template <>
struct __IsInteger<unsigned long> : TrueType
{
};

template <>
struct __IsInteger<long long> : TrueType
{
};

template <>
struct __IsInteger<unsigned long long> : TrueType
{
};

// Floating point
template <typename, typename = void>
struct __IsFloating : FalseType
{
};

template <>
struct __IsFloating<float> : TrueType
{
};

template <>
struct __IsFloating<double> : TrueType
{
};

template <>
struct __IsFloating<long double> : TrueType
{
};

template <class T>
struct __IsArray : FalseType
{
};

template <class T>
struct __IsArray<T[]> : TrueType
{
};

template <class T, std::size_t N>
struct __IsArray<T[N]> : TrueType
{
};

template <class T>
struct __IsPointer : FalseType
{
};

template <class T>
struct __IsPointer<T*> : TrueType
{
};

template <class T>
struct __IsPointer<T* const> : TrueType
{
};

template <class T>
struct __IsPointer<T* volatile> : TrueType
{
};

template <class T>
struct __IsPointer<T* const volatile> : TrueType
{
};

template <typename T>
struct __IsLValueReference : FalseType
{
};

template <typename T>
struct __IsLValueReference<T&> : TrueType
{
};

template <typename T>
struct __IsRValueReference : FalseType
{
};

template <typename T>
struct __IsRValueReference<T&&> : TrueType
{
};

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_
