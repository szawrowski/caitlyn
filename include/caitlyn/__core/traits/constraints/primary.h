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

#ifndef CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_
#define CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_

#include "caitlyn/__core/traits/types/primary.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr bool is_void() {
  return traits::is_void_t<T>::value;
}

template <typename T>
constexpr bool is_null_pointer() {
  return traits::is_null_pointer_t<T>::value;
}

template <typename T>
constexpr bool is_boolean() {
  return traits::is_boolean_t<T>::value;
}

template <typename T>
constexpr bool is_character() {
  return traits::is_character_t<T>::value;
}

template <typename T>
constexpr bool is_integer() {
  return traits::is_integer_t<T>::value;
}

template <typename T>
constexpr bool is_integral() {
  return traits::is_character_t<T>::value || traits::is_integer_t<T>::value ||
         traits::is_boolean_t<T>::value;
}

template <typename T>
constexpr bool is_floating() {
  return traits::is_floating_t<T>::value;
}

template <typename T>
constexpr bool is_array() {
  return traits::is_array_t<T>::value;
}

template <typename T>
constexpr bool is_enum() {
  return std::is_enum<T>::value;
}

template <typename T>
constexpr bool is_union() {
  return std::is_union<T>::value;
}

template <typename T>
constexpr bool is_class() {
  return std::is_class<T>::value;
}

template <typename T>
constexpr bool is_function() {
  return std::is_function<T>::value;
}

template <typename T>
constexpr bool is_pointer() {
  return traits::is_pointer_t<T>::value;
}

template <typename T>
constexpr bool is_lvalue_reference() {
  return traits::is_lvalue_reference_t<T>::value;
}

template <typename T>
constexpr bool is_rvalue_reference() {
  return traits::is_lvalue_reference_t<T>::value;
}

template <typename T>
constexpr bool is_member_object_pointer() {
  return std::is_member_object_pointer<T>::value;
}

template <typename T>
constexpr bool is_member_function_pointer() {
  return std::is_member_function_pointer<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_CONSTRAINTS_PRIMARY_H_
