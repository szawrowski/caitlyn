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

#ifndef CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_
#define CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_

#include "caitlyn/core/traits/types/base.h"

namespace cait {
namespace traits {

template <typename T>
struct add_const_t {
  using type = const T;
};

template <typename T>
struct add_volatile_t {
  using type = const T;
};

template <typename T>
struct add_cv_t {
  using type = const volatile T;
};

template <typename T>
struct remove_cv_t {
  using type = T;
};

template <typename T>
struct remove_cv_t<const T> {
  using type = T;
};

template <typename T>
struct remove_cv_t<volatile T> {
  using type = T;
};

template <typename T>
struct remove_cv_t<const volatile T> {
  using type = T;
};

}  // namespace traits

template <typename T>
using add_const_t = typename traits::add_const_t<T>::type;

template <typename T>
using add_volatile_t = typename traits::add_volatile_t<T>::type;

template <typename T>
using outfit_t = typename traits::add_cv_t<T>::type;

template <typename T>
using remove_const = typename traits::remove_cv_t<const T>::type;

template <typename T>
using remove_volatile = typename traits::remove_cv_t<volatile T>::type;

template <typename T>
using clean_t = typename traits::remove_cv_t<T>::type;

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_SPECIFIERS_H_
