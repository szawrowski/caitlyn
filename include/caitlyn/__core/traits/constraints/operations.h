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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_OPERATIONS_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_OPERATIONS_H_

#include "caitlyn/__core/traits/types/base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr bool constructible()
{
    return std::is_constructible<T>::value;
}

template <typename T>
constexpr bool trivially_constructible()
{
    return std::is_trivially_constructible<T>::value;
}

template <typename T>
constexpr bool nothrow_constructible()
{
    return std::is_nothrow_constructible<T>::value;
}

template <typename T>
constexpr bool default_constructible()
{
    return std::is_default_constructible<T>::value;
}

template <typename T>
constexpr bool trivially_default_constructible()
{
    return std::is_trivially_default_constructible<T>::value;
}

template <typename T>
constexpr bool nothrow_default_constructible()
{
    return std::is_nothrow_default_constructible<T>::value;
}

template <typename T>
constexpr bool copy_constructible()
{
    return std::is_copy_constructible<T>::value;
}

template <typename T>
constexpr bool trivially_copy_constructible()
{
    return std::is_trivially_copy_constructible<T>::value;
}

template <typename T>
constexpr bool nothrow_copy_constructible()
{
    return std::is_nothrow_copy_constructible<T>::value;
}

template <typename T>
constexpr bool move_constructible()
{
    return std::is_move_constructible<T>::value;
}

template <typename T>
constexpr bool trivially_move_constructible()
{
    return std::is_trivially_move_constructible<T>::value;
}

template <typename T>
constexpr bool nothrow_move_constructible()
{
    return std::is_nothrow_move_constructible<T>::value;
}

template <typename T, typename U>
constexpr bool assignable()
{
    return std::is_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr bool trivially_assignable()
{
    return std::is_trivially_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr bool nothrow_assignable()
{
    return std::is_nothrow_assignable<T, U>::value;
}

template <typename T>
constexpr bool copy_assignable()
{
    return std::is_copy_assignable<T>::value;
}

template <typename T>
constexpr bool trivially_copy_assignable()
{
    return std::is_trivially_copy_assignable<T>::value;
}

template <typename T>
constexpr bool nothrow_copy_assignable()
{
    return std::is_nothrow_copy_assignable<T>::value;
}

template <typename T>
constexpr bool move_assignable()
{
    return std::is_move_assignable<T>::value;
}

template <typename T>
constexpr bool trivially_move_assignable()
{
    return std::is_trivially_move_assignable<T>::value;
}

template <typename T>
constexpr bool nothrow_move_assignable()
{
    return std::is_nothrow_move_assignable<T>::value;
}

template <typename T>
constexpr bool destructible()
{
    return std::is_destructible<T>::value;
}

template <typename T>
constexpr bool trivially_destructible()
{
    return std::is_trivially_destructible<T>::value;
}

template <typename T>
constexpr bool nothrow_destructible()
{
    return std::is_nothrow_destructible<T>::value;
}

template <typename T>
constexpr bool has_virtual_destructor()
{
    return std::has_virtual_destructor<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_OPERATIONS_H_
