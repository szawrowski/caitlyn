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

#include "Caitlyn/__Core/Traits/Types/References.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
auto __TryAddPointer(T*) -> __TypeIdentity<RemoveReferenceType<T>*>;

template <typename T>
auto __TryAddPointer(...) -> __TypeIdentity<T>;

template <typename T>
struct __RemovePointer
{
    using Type = T;
};

template <typename T>
struct __RemovePointer<T*>
{
    using Type = T;
};

template <typename T>
struct __RemovePointer<T* const>
{
    using Type = T;
};

template <typename T>
struct __RemovePointer<T* volatile>
{
    using Type = T;
};

template <typename T>
struct __RemovePointer<T* const volatile>
{
    using Type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using AddPointerType = typename decltype(__Detail::__TryAddPointer<T>(nullptr))::Type;

template <typename T>
using RemovePointerType = typename __Detail::__RemovePointer<T>::Type;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_
