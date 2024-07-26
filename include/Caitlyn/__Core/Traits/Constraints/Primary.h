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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_

#include "Caitlyn/__Core/Traits/Types/Primary.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr bool IsVoid()
{
    return traits::IsVoidType<T>::Value;
}

template <typename T>
constexpr bool IsNullPointer()
{
    return traits::IsNullPointerType<T>::Value;
}

template <typename T>
constexpr bool IsBoolean()
{
    return traits::IsBooleanType<T>::Value;
}

template <typename T>
constexpr bool IsCharacter()
{
    return traits::IsCharacterType<T>::Value;
}

template <typename T>
constexpr bool IsInteger()
{
    return traits::IsIntegerType<T>::Value;
}

template <typename T>
constexpr bool IsIntegral()
{
    return traits::IsCharacterType<T>::Value || traits::IsIntegerType<T>::Value || traits::IsBooleanType<T>::Value;
}

template <typename T>
constexpr bool IsFloating()
{
    return traits::IsFloatingType<T>::Value;
}

template <typename T>
constexpr bool IsArray()
{
    return traits::IsArrayType<T>::Value;
}

template <typename T>
constexpr bool IsEnum()
{
    return std::is_enum<T>::value;
}

template <typename T>
constexpr bool IsUnion()
{
    return std::is_union<T>::value;
}

template <typename T>
constexpr bool IsClass()
{
    return std::is_class<T>::value;
}

template <typename T>
constexpr bool IsFunction()
{
    return std::is_function<T>::value;
}

template <typename T>
constexpr bool IsPointer()
{
    return traits::IsPointerType<T>::Value;
}

template <typename T>
constexpr bool IsLValueReference()
{
    return traits::IsLValueReferenceType<T>::Value;
}

template <typename T>
constexpr bool IsRValueReference()
{
    return traits::IsLValueReferenceType<T>::Value;
}

template <typename T>
constexpr bool IsMemberObjectPointer()
{
    return std::is_member_object_pointer<T>::value;
}

template <typename T>
constexpr bool IsMemberFunctionPointer()
{
    return std::is_member_function_pointer<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_
