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

#ifndef CAITLUN_CORE_TRAITS_TYPES_BASE_H_
#define CAITLUN_CORE_TRAITS_TYPES_BASE_H_

#include <type_traits>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <Bool B>
struct BooleanConstant
{
    using ValueType = decltype(B);
    using Type = BooleanConstant;

public:
    constexpr explicit operator ValueType() const noexcept
    {
        return Value;
    }

    constexpr ValueType operator()() const noexcept
    {
        return Value;
    }

public:
    static constexpr Bool Value = B;
};

using TrueType = BooleanConstant<true>;
using FalseType = BooleanConstant<false>;

template <typename...>
using Indicator = void;

template <Bool, typename = void>
struct Constraint
{
};

template <typename Ret>
struct Constraint<true, Ret>
{
    using Type = Ret;
};

template <Bool Condition, typename Ret = void>
using Required = typename Constraint<Condition, Ret>::Type;

template <typename T>
struct TypeIdentity
{
    using Type = T;
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLUN_CORE_TRAITS_TYPES_BASE_H_
