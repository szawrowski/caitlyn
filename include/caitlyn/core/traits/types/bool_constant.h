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

#ifndef CAITLUN_CORE_TRAITS_TYPES_INTEGRAL_CONSTANT_H_
#define CAITLUN_CORE_TRAITS_TYPES_INTEGRAL_CONSTANT_H_

namespace cait {
namespace traits {

template <bool B>
struct bool_constant_t {
  using value_type = bool;
  using type = bool_constant_t;

  constexpr explicit operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }

  static constexpr bool value = B;
};

}  // namespace traits

using true_t = traits::bool_constant_t<true>;
using false_t = traits::bool_constant_t<false>;

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_INTEGRAL_CONSTANT_H_
