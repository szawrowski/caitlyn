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

#ifndef CAITLUN_CORE_TRAITS_TYPES_REFERENCES_H_
#define CAITLUN_CORE_TRAITS_TYPES_REFERENCES_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
auto TryAddLValueReference(T*) -> TypeIdentity<T&>;

template <typename T>
auto TryAddLValueReference(...) -> TypeIdentity<T>;

template <typename T>
auto TryAddRValueReference(T*) -> TypeIdentity<T&&>;

template <typename T>
auto TryAddRValueReference(...) -> TypeIdentity<T>;

template <typename T>
struct RemoveReferenceType
{
    using Type = T;
};

template <typename T>
struct RemoveReferenceType<T&>
{
    using Type = T;
};

template <typename T>
struct RemoveReferenceType<T&&>
{
    using Type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using AddLValueReferenceType = typename decltype(__detail::TryAddLValueReference<T>(nullptr))::Type;

template <typename T>
using AddRValueReferenceType = typename decltype(__detail::TryAddRValueReference<T>(nullptr))::Type;

template <typename T>
using RemoveReferenceType = typename __detail::RemoveReferenceType<T>::Type;

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_REFERENCES_H_
