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

#ifndef CAITLYN_CORE_TREITS_H_
#define CAITLYN_CORE_TREITS_H_

#include "caitlyn/__core/traits/constraints.h"
#include "caitlyn/__core/traits/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <bool B>
using condition = traits::condition_t<B>;

using true_type = traits::true_t;
using false_type = traits::false_t;

template <typename... Args>
using indicator = traits::indicator_t<Args...>;

template <bool Condition, typename Ret = void>
using required = traits::required_t<Condition, Ret>;

template <typename T>
using add_lvalue_reference = traits::add_lvalue_reference_t<T>;

template <typename T>
using add_rvalue_reference = traits::add_rvalue_reference_t<T>;

template <typename T>
using remove_reference = traits::remove_reference_t<T>;

template <typename T>
using add_pointer = traits::add_pointer_t<T>;

template <typename T>
using remove_pointer = traits::remove_pointer_t<T>;

template <typename T>
T&& make_movable(T& value) {
  return static_cast<T&&>(value);
}

template <typename T>
T&& forward(traits::remove_reference_t<T>& value) noexcept {
  return static_cast<T&&>(value);
}

template <typename T>
T&& forward(traits::remove_reference_t<T>&& value) noexcept {
  static_assert(!traits::is_lvalue_reference_t<T>::value, "bad forward call");
  return static_cast<T&&>(value);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_TREITS_H_
