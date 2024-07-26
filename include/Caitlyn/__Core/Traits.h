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

#ifndef CAITLYN_CORE_TREITS_H_
#define CAITLYN_CORE_TREITS_H_

#include "Caitlyn/__Core/Traits/Constraints.h"
#include "Caitlyn/__Core/Traits/Types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
using AddLValueReference = Traits::AddLValueReferenceType<T>;

template <typename T>
using AddRValueReference = Traits::AddRValueReferenceType<T>;

template <typename T>
using RemoveReference = Traits::RemoveReferenceType<T>;

template <typename T>
using AddPointer = Traits::AddPointerType<T>;

template <typename T>
using RemovePointer = Traits::RemovePointerType<T>;

template <typename T>
T&& MakeMovable(T& value)
{
    return static_cast<T&&>(value);
}

template <typename T>
T&& Forward(Traits::RemoveReferenceType<T>& value) noexcept
{
    return static_cast<T&&>(value);
}

template <typename T>
T&& Forward(Traits::RemoveReferenceType<T>&& value) noexcept
{
    static_assert(!Traits::IsLValueReferenceType<T>::value, "Bad forward call");
    return static_cast<T&&>(value);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TREITS_H_
