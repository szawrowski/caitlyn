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

#ifndef CAITLUN_CORE_TRAITS_TYPES_SAME_H_
#define CAITLUN_CORE_TRAITS_TYPES_SAME_H_

#include "caitlyn/core/traits/types/bool_constant.h"

namespace cait {
namespace traits {

template <typename, typename>
struct is_same_t : false_t {};

template <typename T>
struct is_same_t<T, T> : true_t {};

}  // namespace traits

template <typename T>
constexpr bool is_same() {
  return traits::is_same_t<T, T>::value;
}

template <typename T, typename U>
constexpr bool is_not_same() {
  return !traits::is_same_t<T, U>::value;
}

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_SAME_H_
