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
T&& MakeMovable(T& value)
{
    return static_cast<T&&>(value);
}

template <typename T>
T&& Forward(RemoveReferenceType<T>& value) noexcept
{
    return static_cast<T&&>(value);
}

template <typename T>
T&& Forward(RemoveReferenceType<T>&& value) noexcept
{
    static_assert(!IsLValueReference<T>(), "Bad forward call");
    return static_cast<T&&>(value);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TREITS_H_
