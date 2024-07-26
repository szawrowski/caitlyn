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

#ifndef CAITLYN_CORE_TRAITS_TYPES_OPERATORS_H_
#define CAITLYN_CORE_TRAITS_TYPES_OPERATORS_H_

#include <iostream>

#include "Caitlyn/__Core/Traits/Types/Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename, typename = void>
struct HasLessOperatorType : FalseType
{
};

template <typename T>
struct HasLessOperatorType<T, Indicator<decltype(std::declval<T>() < std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasGreaterOperatorType : FalseType
{
};

template <typename T>
struct HasGreaterOperatorType<T, Indicator<decltype(std::declval<T>() > std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasAddOperatorType : FalseType
{
};

template <typename T>
struct HasAddOperatorType<T, Indicator<decltype(std::declval<T>() + std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasSubtractOperatorType : FalseType
{
};

template <typename T>
struct HasSubtractOperatorType<T, Indicator<decltype(std::declval<T>() - std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasMultyplyOperatorType : FalseType
{
};

template <typename T>
struct HasMultyplyOperatorType<T, Indicator<decltype(std::declval<T>() * std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasDivideOperatorType : FalseType
{
};

template <typename T>
struct HasDivideOperatorType<T, Indicator<decltype(std::declval<T>() / std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasModulusOperatorType : FalseType
{
};

template <typename T>
struct HasModulusOperatorType<T, Indicator<decltype(std::declval<T>() % std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasEqualOperatorType : FalseType
{
};

template <typename T>
struct HasEqualOperatorType<T, Indicator<decltype(std::declval<T>() == std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasNotEqualOperatorType : FalseType
{
};

template <typename T>
struct HasNotEqualOperatorType<T, Indicator<decltype(std::declval<T>() != std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasSubscriptOperatorType : FalseType
{
};

template <typename T>
struct HasSubscriptOperatorType<T, Indicator<decltype(std::declval<T>()[std::declval<T>()])>> : TrueType
{
};

template <typename, typename = void>
struct HasIncrementOperatorType : FalseType
{
};

template <typename T>
struct HasIncrementOperatorType<T, Indicator<decltype(++std::declval<T&>())>> : TrueType
{
};

template <typename, typename = void>
struct HasDecrementOperatorType : FalseType
{
};

template <typename T>
struct HasDecrementOperatorType<T, Indicator<decltype(--std::declval<T&>())>> : TrueType
{
};

template <typename, typename = void>
struct HasBitwiseAndOperatorType : FalseType
{
};

template <typename T>
struct HasBitwiseAndOperatorType<T, Indicator<decltype(std::declval<T>() & std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasBitwiseOrOperatorType : FalseType
{
};

template <typename T>
struct HasBitwiseOrOperatorType<T, Indicator<decltype(std::declval<T>() & std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasBitwiseXorOperatorType : FalseType
{
};

template <typename T>
struct HasBitwiseXorOperatorType<T, Indicator<decltype(std::declval<T>() ^ std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasLeftShiftOperatorType : FalseType
{
};

template <typename T>
struct HasLeftShiftOperatorType<T, Indicator<decltype(std::declval<T>() << std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasRightShiftOperatorType : FalseType
{
};

template <typename T>
struct HasRightShiftOperatorType<T, Indicator<decltype(std::declval<T>() >> std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasIStreamOperatorType : FalseType
{
};

template <typename T>
struct HasIStreamOperatorType<T, Indicator<decltype(std::declval<std::istream&>() >> std::declval<T>())>> : TrueType
{
};

template <typename, typename = void>
struct HasOStreamOperatorType : FalseType
{
};

template <typename T>
struct HasOStreamOperatorType<T, Indicator<decltype(std::declval<std::ostream&>() << std::declval<T>())>> : TrueType
{
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_TRAITS_TYPES_OPERATORS_H_
