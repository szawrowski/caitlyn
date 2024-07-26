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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTIES_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTIES_H_

#include "caitlyn/__core/Traits/types/properties.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr bool Const()
{
    return std::is_const<T>::value;
}

template <typename T>
constexpr bool Volatile()
{
    return std::is_volatile<T>::value;
}

template <typename T>
constexpr bool Trivial()
{
    return std::is_trivial<T>::value;
}

template <typename T>
constexpr bool TriviallyCopyable()
{
    return std::is_trivially_copyable<T>::value;
}

template <typename T>
constexpr bool StandardLayout()
{
    return std::is_standard_layout<T>::value;
}

template <typename T>
constexpr bool Empty()
{
    return std::is_empty<T>::value;
}

template <typename T>
constexpr bool Polymorphic()
{
    return std::is_polymorphic<T>::value;
}

template <typename T>
constexpr bool Abstract()
{
    return std::is_abstract<T>::value;
}

template <typename T>
constexpr bool Signed()
{
    return Traits::IsSignedType<T>::Value;
}

template <typename T>
constexpr bool Unsigned()
{
    return Traits::IsUnsignedType<T>::Value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTIES_H_
