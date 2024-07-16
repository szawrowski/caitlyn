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

#ifndef CAITLYN_CORE_UTILITY_COMPARATORS_H_
#define CAITLYN_CORE_UTILITY_COMPARATORS_H_

#include "caitlyn/__base.h"

namespace cait {

template <typename T, typename U>
__caitlyn_constexpr14 bool cmp_eq(T t, U u) noexcept {
  using UT = typename std::make_unsigned<T>::type;
  using UU = typename std::make_unsigned<U>::type;

  if (std::is_signed<T>::value == std::is_signed<U>::value) {
    return t == u;
  }
  if (std::is_signed<T>::value) {
    return t >= 0 && UT(t) == u;
  }
  return u >= 0 && t == UU(u);
}

template <typename T, typename U>
constexpr bool cmp_ne(T t, U u) noexcept {
  return !compare_equal(t, u);
}

template <typename T, typename U>
__caitlyn_constexpr14 bool cmp_less(T t, U u) noexcept {
  using UT = typename std::make_unsigned<T>::type;
  using UU = typename std::make_unsigned<U>::type;

  if (std::is_signed<T>::value == std::is_signed<U>::value) {
    return t < u;
  }
  if (std::is_signed<T>::value) {
    return t < 0 || UT(t) < u;
  }
  return u >= 0 && t < UU(u);
}

template <typename T, typename U>
constexpr bool cmp_greater(T t, U u) noexcept {
  return compare_less(u, t);
}

template <typename T, typename U>
constexpr bool cmp_le(T t, U u) noexcept {
  return !compare_greater(t, u);
}

template <typename T, typename U>
constexpr bool cmp_ge(T t, U u) noexcept {
  return !compare_less(t, u);
}

}  // namespace cait

#endif  // CAITLYN_CORE_UTILITY_COMPARATORS_H_
