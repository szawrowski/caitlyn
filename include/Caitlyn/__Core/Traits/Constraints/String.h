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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename, typename = void>
struct Has_to_string_Type : FalseType
{
};

template <typename T>
struct Has_to_string_Type<T, Indicator<decltype(std::declval<T>().to_string())>> : TrueType
{
};

template <typename, typename = void>
struct Has_str_Type : FalseType
{
};

template <typename T>
struct Has_str_Type<T, Indicator<decltype(std::declval<T>().str())>> : TrueType
{
};

template <typename, typename = void>
struct Has_c_str_Type : FalseType
{
};

template <typename T>
struct Has_c_str_Type<T, Indicator<decltype(std::declval<T>().c_str())>> : TrueType
{
};

template <typename, typename = void>
struct Has_ToString_Type : FalseType
{
};

template <typename T>
struct Has_ToString_Type<T, Indicator<decltype(std::declval<T>().ToString())>> : TrueType
{
};

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
constexpr Bool Has_to_string()
{
    return Traits::Has_to_string_Type<T>::Value;
}

template <typename T>
constexpr Bool Has_str()
{
    return Traits::Has_str_Type<T>::Value;
}

template <typename T>
constexpr Bool Has_c_str()
{
    return Traits::Has_c_str_Type<T>::Value;
}

template <typename T>
constexpr Bool ConvertibleToString()
{
    return Traits::Has_ToString_Type<T>::Value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_
