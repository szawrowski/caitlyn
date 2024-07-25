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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTY_QUERIES_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTY_QUERIES_H_

#include <type_traits>

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr bool alignment_of()
{
    return std::alignment_of<T>::value;
}

template <typename T>
constexpr bool rank()
{
    return std::rank<T>::value;
}

template <typename T>
constexpr bool extent()
{
    return std::extent<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_PROPERTY_QUERIES_H_
