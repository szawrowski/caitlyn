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

#ifndef CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_
#define CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
struct AddConst
{
    using Type = const T;
};

template <typename T>
struct AddVolatile
{
    using Type = const T;
};

template <typename T>
struct AddCV
{
    using Type = const volatile T;
};

template <typename T>
struct RemoveCV
{
    using Type = T;
};

template <typename T>
struct RemoveCV<const T>
{
    using Type = T;
};

template <typename T>
struct RemoveCV<volatile T>
{
    using Type = T;
};

template <typename T>
struct RemoveCV<const volatile T>
{
    using Type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using AddConstType = typename __detail::AddConst<T>::Type;

template <typename T>
using AddVolatileType = typename __detail::AddVolatile<T>::Type;

template <typename T>
using AddCVType = typename __detail::AddCV<T>::Type;

template <typename T>
using RemoveConstType = typename __detail::RemoveCV<const T>::Type;

template <typename T>
using RemoveVolatileType = typename __detail::RemoveCV<volatile T>::Type;

template <typename T>
using RemoveCVType = typename __detail::RemoveCV<T>::Type;

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
using AddConst = traits::AddConstType<T>;

template <typename T>
using AddVolatile = traits::AddVolatileType<T>;

template <typename T>
using AddCV = traits::AddCVType<T>;

template <typename T>
using RemoveConst = traits::RemoveConstType<T>;

template <typename T>
using RemoveVolatile = traits::RemoveVolatileType<T>;

template <typename T>
using RemoveCV = traits::RemoveCVType<T>;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_
