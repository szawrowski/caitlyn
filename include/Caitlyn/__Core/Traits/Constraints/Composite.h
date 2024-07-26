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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_COMPOSITE_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_COMPOSITE_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr Bool IsFundamental()
{
    return std::is_fundamental<T>::value;
}

template <typename T>
constexpr Bool IsArithmetic()
{
    return std::is_arithmetic<T>::value;
}

template <typename T>
constexpr Bool IsScalar()
{
    return std::is_scalar<T>::value;
}

template <typename T>
constexpr Bool IsObject()
{
    return std::is_object<T>::value;
}

template <typename T>
constexpr Bool IsCompound()
{
    return std::is_compound<T>::value;
}

template <typename T>
constexpr Bool IsReference()
{
    return std::is_reference<T>::value;
}

template <typename T>
constexpr Bool IsMemberPointer()
{
    return std::is_member_pointer<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_COMPOSITE_H_
