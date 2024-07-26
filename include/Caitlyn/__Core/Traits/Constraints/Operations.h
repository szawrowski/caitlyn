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

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr Bool Constructible()
{
    return std::is_constructible<T>::value;
}

template <typename T>
constexpr Bool TriviallyConstructible()
{
    return std::is_trivially_constructible<T>::value;
}

template <typename T>
constexpr Bool NothrowConstructible()
{
    return std::is_nothrow_constructible<T>::value;
}

template <typename T>
constexpr Bool DefaultConstructible()
{
    return std::is_default_constructible<T>::value;
}

template <typename T>
constexpr Bool TriviallyDefaultConstructible()
{
    return std::is_trivially_default_constructible<T>::value;
}

template <typename T>
constexpr Bool NothrowDefaultConstructible()
{
    return std::is_nothrow_default_constructible<T>::value;
}

template <typename T>
constexpr Bool CopyConstructible()
{
    return std::is_copy_constructible<T>::value;
}

template <typename T>
constexpr Bool TriviallyCopyConstructible()
{
    return std::is_trivially_copy_constructible<T>::value;
}

template <typename T>
constexpr Bool NothrowCopyConstructible()
{
    return std::is_nothrow_copy_constructible<T>::value;
}

template <typename T>
constexpr Bool MoveConstructible()
{
    return std::is_move_constructible<T>::value;
}

template <typename T>
constexpr Bool TriviallyMoveConstructible()
{
    return std::is_trivially_move_constructible<T>::value;
}

template <typename T>
constexpr Bool NothrowMoveConstructible()
{
    return std::is_nothrow_move_constructible<T>::value;
}

template <typename T, typename U>
constexpr Bool Assignable()
{
    return std::is_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr Bool TriviallyAssignable()
{
    return std::is_trivially_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr Bool NothrowAssignable()
{
    return std::is_nothrow_assignable<T, U>::value;
}

template <typename T>
constexpr Bool CopyAssignable()
{
    return std::is_copy_assignable<T>::value;
}

template <typename T>
constexpr Bool TriviallyCopyAssignable()
{
    return std::is_trivially_copy_assignable<T>::value;
}

template <typename T>
constexpr Bool NothrowCopyAssignable()
{
    return std::is_nothrow_copy_assignable<T>::value;
}

template <typename T>
constexpr Bool MoveAssignable()
{
    return std::is_move_assignable<T>::value;
}

template <typename T>
constexpr Bool TriviallyMoveAssignable()
{
    return std::is_trivially_move_assignable<T>::value;
}

template <typename T>
constexpr Bool NothrowMoveAssignable()
{
    return std::is_nothrow_move_assignable<T>::value;
}

template <typename T>
constexpr Bool Destructible()
{
    return std::is_destructible<T>::value;
}

template <typename T>
constexpr Bool TriviallyDestructible()
{
    return std::is_trivially_destructible<T>::value;
}

template <typename T>
constexpr Bool NothrowDestructible()
{
    return std::is_nothrow_destructible<T>::value;
}

template <typename T>
constexpr Bool HasVirtualDestructor()
{
    return std::has_virtual_destructor<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_OPERATIONS_H_
