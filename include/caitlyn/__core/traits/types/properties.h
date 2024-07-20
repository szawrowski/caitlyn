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

#ifndef CAITLUN_CORE_TRAITS_TYPES_PROPERTIES_H_
#define CAITLUN_CORE_TRAITS_TYPES_PROPERTIES_H_

#include "caitlyn/__core/traits/types/composite.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename T, bool = is_arithmetic<T>()>
struct is_signed_t : condition_t<T(-1) < T(0)> {};

template <typename T, bool = is_arithmetic<T>()>
struct is_unsigned_t : condition_t<T(0) < T(-1)> {};

__CAITLYN_TRAITS_NAMESPACE_END

template <typename T>
constexpr bool is_const() {
  return std::is_const<T>::value;
}

template <typename T>
constexpr bool is_volatile() {
  return std::is_volatile<T>::value;
}

template <typename T>
constexpr bool is_trivial() {
  return std::is_trivial<T>::value;
}

template <typename T>
constexpr bool trivially_copyable() {
  return std::is_trivially_copyable<T>::value;
}

template <typename T>
constexpr bool is_standard_layout() {
  return std::is_standard_layout<T>::value;
}

template <typename T>
constexpr bool is_empty() {
  return std::is_empty<T>::value;
}

template <typename T>
constexpr bool is_polymorphic() {
  return std::is_polymorphic<T>::value;
}

template <typename T>
constexpr bool is_abstract() {
  return std::is_abstract<T>::value;
}

template <typename T>
constexpr bool is_signed() {
  return traits::is_signed_t<T>::value;
}

template <typename T>
constexpr bool is_unsigned() {
  return traits::is_unsigned_t<T>::value;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_PROPERTIES_H_
