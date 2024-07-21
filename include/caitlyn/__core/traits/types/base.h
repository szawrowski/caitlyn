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

#ifndef CAITLUN_CORE_TRAITS_TYPES_BASE_H_
#define CAITLUN_CORE_TRAITS_TYPES_BASE_H_

#include <type_traits>

#include "caitlyn/__base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <bool B>
struct condition_t {
  using value_type = bool;
  using type = condition_t;

public:
  constexpr explicit operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }

public:
  static constexpr bool value = B;
};

using true_t = condition_t<true>;
using false_t = condition_t<false>;

template <typename...>
using indicator_t = void;

template <bool, typename = void>
struct constraint_t {};

template <typename Ret>
struct constraint_t<true, Ret> {
  using type = Ret;
};

template <bool Condition, typename Ret = void>
using required_t = typename constraint_t<Condition, Ret>::type;

template <typename T>
struct type_identity_t {
  using type = T;
};

__CAITLYN_TRAITS_NAMESPACE_END

template <bool B>
using condition = traits::condition_t<B>;

using true_type = traits::true_t;
using false_type = traits::false_t;

template <typename... Args>
using indicator = traits::indicator_t<Args...>;

template <bool Condition, typename Ret = void>
using required = traits::required_t<Condition, Ret>;

template <typename T>
using type_identity = traits::type_identity_t<T>;

template <typename T>
T&& make_movable(T& value) {
  return static_cast<T&&>(value);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_BASE_H_
