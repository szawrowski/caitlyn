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

#ifndef CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_
#define CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
auto TryAddPointer(T*) -> TypeIdentity<typename std::remove_reference<T>::type*>;

template <typename T>
auto TryAddPointer(...) -> TypeIdentity<T>;

template <typename T>
struct RemoveReference
{
    using Type = T;
};

template <typename T>
struct RemoveReference<T*>
{
    using Type = T;
};

template <typename T>
struct RemoveReference<T* const>
{
    using Type = T;
};

template <typename T>
struct RemoveReference<T* volatile>
{
    using Type = T;
};

template <typename T>
struct RemoveReference<T* const volatile>
{
    using Type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using AddPointerType = typename decltype(__Detail::TryAddPointer<T>(nullptr))::Type;

template <typename T>
using RemovePointerType = typename __Detail::RemoveReference<T>::Type;

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_
