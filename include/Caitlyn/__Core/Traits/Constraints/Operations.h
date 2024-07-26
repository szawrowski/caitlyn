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
constexpr bool Constructible()
{
    return std::is_constructible<T>::value;
}

template <typename T>
constexpr bool TriviallyConstructible()
{
    return std::is_trivially_constructible<T>::value;
}

template <typename T>
constexpr bool NothrowConstructible()
{
    return std::is_nothrow_constructible<T>::value;
}

template <typename T>
constexpr bool DefaultConstructible()
{
    return std::is_default_constructible<T>::value;
}

template <typename T>
constexpr bool TriviallyDefaultConstructible()
{
    return std::is_trivially_default_constructible<T>::value;
}

template <typename T>
constexpr bool NothrowDefaultConstructible()
{
    return std::is_nothrow_default_constructible<T>::value;
}

template <typename T>
constexpr bool CopyConstructible()
{
    return std::is_copy_constructible<T>::value;
}

template <typename T>
constexpr bool TriviallyCopyConstructible()
{
    return std::is_trivially_copy_constructible<T>::value;
}

template <typename T>
constexpr bool NothrowCopyConstructible()
{
    return std::is_nothrow_copy_constructible<T>::value;
}

template <typename T>
constexpr bool MoveConstructible()
{
    return std::is_move_constructible<T>::value;
}

template <typename T>
constexpr bool TriviallyMoveConstructible()
{
    return std::is_trivially_move_constructible<T>::value;
}

template <typename T>
constexpr bool NothrowMoveConstructible()
{
    return std::is_nothrow_move_constructible<T>::value;
}

template <typename T, typename U>
constexpr bool Assignable()
{
    return std::is_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr bool TriviallyAssignable()
{
    return std::is_trivially_assignable<T, U>::value;
}

template <typename T, typename U>
constexpr bool NothrowAssignable()
{
    return std::is_nothrow_assignable<T, U>::value;
}

template <typename T>
constexpr bool CopyAssignable()
{
    return std::is_copy_assignable<T>::value;
}

template <typename T>
constexpr bool TriviallyCopyAssignable()
{
    return std::is_trivially_copy_assignable<T>::value;
}

template <typename T>
constexpr bool NothrowCopyAssignable()
{
    return std::is_nothrow_copy_assignable<T>::value;
}

template <typename T>
constexpr bool MoveAssignable()
{
    return std::is_move_assignable<T>::value;
}

template <typename T>
constexpr bool TriviallyMoveAssignable()
{
    return std::is_trivially_move_assignable<T>::value;
}

template <typename T>
constexpr bool NothrowMoveAssignable()
{
    return std::is_nothrow_move_assignable<T>::value;
}

template <typename T>
constexpr bool Destructible()
{
    return std::is_destructible<T>::value;
}

template <typename T>
constexpr bool TriviallyDestructible()
{
    return std::is_trivially_destructible<T>::value;
}

template <typename T>
constexpr bool NothrowDestructible()
{
    return std::is_nothrow_destructible<T>::value;
}

template <typename T>
constexpr bool HasVirtualDestructor()
{
    return std::has_virtual_destructor<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_CONSTRAINTS_OPERATIONS_H_
