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

namespace cait {

template <bool B>
struct condition_t {
  using value_type = bool;
  using type = condition_t;

  constexpr explicit operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }

  static constexpr bool value = B;
};

using true_t = condition_t<true>;
using false_t = condition_t<false>;

template<typename...>
using indicator_t = void;

template<bool, typename = void>
struct constraint_t {};

template<typename Ret>
struct constraint_t<true, Ret> {
  using type = Ret;
};

template <bool Condition, typename Ret = void>
using required_t = typename constraint_t<Condition, Ret>::type;

template <typename T>
struct type_identity_t {
  using type = T;
};

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_BASE_H_
