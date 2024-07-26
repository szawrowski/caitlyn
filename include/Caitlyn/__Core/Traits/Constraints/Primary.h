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
constexpr Bool IsVoid()
{
    return IsVoidType<T>::Value;
}

template <typename T>
constexpr Bool IsNullPointer()
{
    return IsNullPointerType<T>::Value;
}

template <typename T>
constexpr Bool IsBoolean()
{
    return IsBooleanType<T>::Value;
}

template <typename T>
constexpr Bool IsCharacter()
{
    return __Detail::__IsCharacter<T>::Value;
}

template <typename T>
constexpr Bool IsInteger()
{
    return __Detail::__IsInteger<T>::Value;
}

template <typename T>
constexpr Bool IsIntegral()
{
    return __Detail::__IsCharacter<T>::Value || __Detail::__IsInteger<T>::Value || IsBooleanType<T>::Value;
}

template <typename T>
constexpr Bool IsFloating()
{
    return __Detail::__IsFloating<T>::Value;
}

template <typename T>
constexpr Bool IsArray()
{
    return __Detail::__IsArray<T>::Value;
}

template <typename T>
constexpr Bool IsEnum()
{
    return std::is_enum<T>::value;
}

template <typename T>
constexpr Bool IsUnion()
{
    return std::is_union<T>::value;
}

template <typename T>
constexpr Bool IsClass()
{
    return std::is_class<T>::value;
}

template <typename T>
constexpr Bool IsFunction()
{
    return std::is_function<T>::value;
}

template <typename T>
constexpr Bool IsPointer()
{
    return __Detail::__IsPointer<T>::Value;
}

template <typename T>
constexpr Bool IsLValueReference()
{
    return __Detail::__IsLValueReference<T>::Value;
}

template <typename T>
constexpr Bool IsRValueReference()
{
    return __Detail::__IsLValueReference<T>::Value;
}

template <typename T>
constexpr Bool IsMemberObjectPointer()
{
    return std::is_member_object_pointer<T>::value;
}

template <typename T>
constexpr Bool IsMemberFunctionPointer()
{
    return std::is_member_function_pointer<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_
