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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H

#include <iostream>

#include "caitlyn/__core/traits/types/base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename, typename = void>
struct has_less_operator_t : false_t {};

template <typename T>
struct has_less_operator_t<
    T, indicator_t<decltype(std::declval<T>() < std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_greater_operator_t : false_t {};

template <typename T>
struct has_greater_operator_t<
    T, indicator_t<decltype(std::declval<T>() > std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_add_operator_t : false_t {};

template <typename T>
struct has_add_operator_t<
    T, indicator_t<decltype(std::declval<T>() + std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_subtract_operator_t : false_t {};

template <typename T>
struct has_subtract_operator_t<
    T, indicator_t<decltype(std::declval<T>() - std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_multyply_operator_t : false_t {};

template <typename T>
struct has_multyply_operator_t<
    T, indicator_t<decltype(std::declval<T>() * std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_divide_operator_t : false_t {};

template <typename T>
struct has_divide_operator_t<
    T, indicator_t<decltype(std::declval<T>() / std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_modulus_operator_t : false_t {};

template <typename T>
struct has_modulus_operator_t<
    T, indicator_t<decltype(std::declval<T>() % std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_equal_operator_t : false_t {};

template <typename T>
struct has_equal_operator_t<
    T, indicator_t<decltype(std::declval<T>() == std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_not_equal_operator_t : false_t {};

template <typename T>
struct has_not_equal_operator_t<
    T, indicator_t<decltype(std::declval<T>() != std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_subscript_operator_t : false_t {};

template <typename T>
struct has_subscript_operator_t<
    T, indicator_t<decltype(std::declval<T>()[std::declval<T>()])>> : true_t {};

template <typename, typename = void>
struct has_increment_operator_t : false_t {};

template <typename T>
struct has_increment_operator_t<T, indicator_t<decltype(++std::declval<T&>())>>
    : true_t {};

template <typename, typename = void>
struct has_decrement_operator_t : false_t {};

template <typename T>
struct has_decrement_operator_t<T, indicator_t<decltype(--std::declval<T&>())>>
    : true_t {};

template <typename, typename = void>
struct has_bitwise_and_operator_t : false_t {};

template <typename T>
struct has_bitwise_and_operator_t<
    T, indicator_t<decltype(std::declval<T>() & std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_bitwise_or_operator_t : false_t {};

template <typename T>
struct has_bitwise_or_operator_t<
    T, indicator_t<decltype(std::declval<T>() & std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_bitwise_xor_operator_t : false_t {};

template <typename T>
struct has_bitwise_xor_operator_t<
    T, indicator_t<decltype(std::declval<T>() ^ std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_left_shift_operator_t : false_t {};

template <typename T>
struct has_left_shift_operator_t<
    T, indicator_t<decltype(std::declval<T>() << std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_right_shift_operator_t : false_t {};

template <typename T>
struct has_right_shift_operator_t<
    T, indicator_t<decltype(std::declval<T>() >> std::declval<T>())>> : true_t {
};

template <typename, typename = void>
struct has_istream_operator_t : false_t {};

template <typename T>
struct has_istream_operator_t<
    T,
    indicator_t<decltype(std::declval<std::istream&>() >> std::declval<T>())>>
    : true_t {};

template <typename, typename = void>
struct has_ostream_operator_t : false_t {};

template <typename T>
struct has_ostream_operator_t<
    T,
    indicator_t<decltype(std::declval<std::ostream&>() << std::declval<T>())>>
    : true_t {};

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H
