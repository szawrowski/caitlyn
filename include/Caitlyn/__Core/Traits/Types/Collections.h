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

#ifndef CAITLYN_CORE_TRAITS_TYPES_COLLECTIONS_H_
#define CAITLYN_CORE_TRAITS_TYPES_COLLECTIONS_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename, typename = void>
struct Has_begin_Type : FalseType
{
};

template <typename T>
struct Has_begin_Type<T, Indicator<decltype(std::declval<T>().begin())>> : TrueType
{
};

template <typename, typename = void>
struct Has_end_Type : FalseType
{
};

template <typename T>
struct Has_end_Type<T, Indicator<decltype(std::declval<T>().end())>> : TrueType
{
};

template <typename, typename = void>
struct Has_push_back_Type : FalseType
{
};

template <typename T>
struct Has_push_back_Type<T, Indicator<decltype(std::declval<T>().push_back(std::declval<typename T::value_type>()))>>
    : TrueType
{
};

template <typename, typename = void>
struct Has_pop_back_Type : FalseType
{
};

template <typename T>
struct Has_pop_back_Type<T, Indicator<decltype(std::declval<T>().pop_back())>> : TrueType
{
};

template <typename, typename = void>
struct Has_size_Type : FalseType
{
};

template <typename T>
struct Has_size_Type<T, Indicator<decltype(std::declval<T>().size())>> : TrueType
{
};

template <typename, typename = void>
struct Has_front_Type : FalseType
{
};

template <typename T>
struct Has_front_Type<T, Indicator<decltype(std::declval<T>().front())>> : TrueType
{
};

template <typename, typename = void>
struct Has_back_Type : FalseType
{
};

template <typename T>
struct Has_back_Type<T, Indicator<decltype(std::declval<T>().back())>> : TrueType
{
};

template <typename, typename = void>
struct Has_data_Type : FalseType
{
};

template <typename T>
struct Has_data_Type<T, Indicator<decltype(std::declval<T>().data())>> : TrueType
{
};

template <typename, typename = void>
struct Has_clear_Type : FalseType
{
};

template <typename T>
struct Has_clear_Type<T, Indicator<decltype(std::declval<T>().clear())>> : TrueType
{
};

template <typename, typename = void>
struct Has_resize_Type : FalseType
{
};

template <typename T>
struct Has_resize_Type<T, Indicator<decltype(std::declval<T>().resize(std::declval<typename T::size_type>()))>>
    : TrueType
{
};

template <typename, typename = void>
struct Has_empty_Type : FalseType
{
};

template <typename T>
struct Has_empty_Type<T, Indicator<decltype(std::declval<T>().empty())>> : TrueType
{
};

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TRAITS_TYPES_COLLECTIONS_H_
