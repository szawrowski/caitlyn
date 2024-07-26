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
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
struct __AddConst
{
    using Type = const T;
};

template <typename T>
struct __AddVolatile
{
    using Type = volatile T;
};

template <typename T>
struct __AddCV
{
    using Type = const volatile T;
};

template <typename T>
struct __RemoveCV
{
    using Type = T;
};

template <typename T>
struct __RemoveCV<const T>
{
    using Type = T;
};

template <typename T>
struct __RemoveCV<volatile T>
{
    using Type = T;
};

template <typename T>
struct __RemoveCV<const volatile T>
{
    using Type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using AddConstType = typename __Detail::__AddConst<T>::Type;

template <typename T>
using AddVolatileType = typename __Detail::__AddVolatile<T>::Type;

template <typename T>
using AddCVType = typename __Detail::__AddCV<T>::Type;

template <typename T>
using RemoveConstType = typename __Detail::__RemoveCV<const T>::Type;

template <typename T>
using RemoveVolatileType = typename __Detail::__RemoveCV<volatile T>::Type;

template <typename T>
using RemoveCVType = typename __Detail::__RemoveCV<T>::Type;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_
