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

#ifndef CAITLUN_CORE_TRAITS_TYPES_COMPOSITE_H_
#define CAITLUN_CORE_TRAITS_TYPES_COMPOSITE_H_

#include "caitlyn/__core/traits/types/primary.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename T>
struct is_arithmetic_t
    : condition_t<is_integer_t<T>::value || is_floating_t<T>::value> {};

template <typename T>
struct is_fundamental_t
    : condition_t<is_arithmetic_t<T>::value || is_void_t<T>::value ||
                  is_null_pointer_t<T>::value> {};

template <class T>
struct is_scalar_t
    : condition_t<is_arithmetic_t<T>::value || std::is_enum<T>::value ||
                  is_pointer_t<T>::value || std::is_member_pointer<T>::value ||
                  is_null_pointer_t<T>::value> {};

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
constexpr bool is_fundamental() {
  return traits::is_fundamental_t<T>::value;
}

template <typename T>
constexpr bool is_arithmetic() {
  return traits::is_arithmetic_t<T>::value;
}

template <typename T>
constexpr bool is_scalar() {
  return traits::is_scalar_t<T>::value;
}

template <typename T>
constexpr bool is_object() {
  return std::is_object<T>::value;
}

template <typename T>
constexpr bool is_compound() {
  return std::is_compound<T>::value;
}

template <typename T>
constexpr bool is_reference() {
  return std::is_reference<T>::value;
}

template <typename T>
constexpr bool is_member_pointer() {
  return std::is_member_pointer<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_COMPOSITE_H_
