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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_RELATIONSHIPS_H_
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_RELATIONSHIPS_H_

#include "Caitlyn/__Core/Traits/Types/Relationships.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T, typename U>
constexpr Bool Same()
{
    return IsSameType<T, U>::Value;
}

template <typename T, typename U>
constexpr Bool Different()
{
    return !IsSameType<T, U>::Value;
}

template <typename Base, typename Derived>
constexpr Bool BaseOf()
{
    return std::is_base_of<Base, Derived>::value;
}

template <typename T, typename U>
constexpr Bool Convertible()
{
    return std::is_convertible<T, U>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TRAITS_CONSTRAINTS_RELATIONSHIPS_H_
