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

#ifndef CAITLUN_CORE_TRAITS_TYPES_BASIC_H_
#define CAITLUN_CORE_TRAITS_TYPES_BASIC_H_

#include <type_traits>

namespace cait {

template <typename T>
constexpr bool is_void() { return std::is_void<T>::value; }

template <typename T>
constexpr bool is_null_ptr() { return std::is_null_pointer<T>::value; }

template <typename T>
constexpr bool is_integral() { return std::is_integral<T>::value; }

template <typename T>
constexpr bool is_floating() { return std::is_floating_point<T>::value; }

template <typename T>
constexpr bool is_array() { return std::is_array<T>::value; }

template <typename T>
constexpr bool is_enum() { return std::is_enum<T>::value; }

template <typename T>
constexpr bool is_union() { return std::is_union<T>::value; }

template <typename T>
constexpr bool is_class() { return std::is_class<T>::value; }

template <typename T>
constexpr bool is_func() { return std::is_function<T>::value; }

template <typename T>
constexpr bool is_ptr() { return std::is_pointer<T>::value; }

template <typename T>
constexpr bool is_lvref() { return std::is_lvalue_reference<T>::value; }

template <typename T>
constexpr bool is_rvref() { return std::is_rvalue_reference<T>::value; }

template <typename T>
constexpr bool is_member_obj_ptr() {
  return std::is_member_object_pointer<T>::value;
}

template <typename T>
constexpr bool is_member_func_ptr() {
  return std::is_member_function_pointer<T>::value;
}

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_BASIC_H_
