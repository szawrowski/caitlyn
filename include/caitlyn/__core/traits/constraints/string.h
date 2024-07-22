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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_

#include "caitlyn/__core/traits/types/base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename, typename = void>
struct has_to_string_t : false_t {};

template <typename T>
struct has_to_string_t<T, indicator_t<decltype(std::declval<T>().to_string())>>
    : true_t {};

template <typename, typename = void>
struct has_str_t : false_t {};

template <typename T>
struct has_str_t<T, indicator_t<decltype(std::declval<T>().str())>> : true_t {};

template <typename, typename = void>
struct has_std_string_t : false_t {};

template <typename T>
struct has_std_string_t<T,
                        indicator_t<decltype(std::declval<T>().std_string())>>
    : true_t {};

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
constexpr bool has_to_string() {
  return traits::has_to_string_t<T>::value;
}

template <typename T>
constexpr bool has_str() {
  return traits::has_str_t<T>::value;
}

template <typename T>
constexpr bool has_std_string() {
    return traits::has_std_string_t<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H_
