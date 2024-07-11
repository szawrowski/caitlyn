// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_COMPARATORS_COMPARATORS_H_
#define CAITLYN_CORE_UTILITY_COMPARATORS_COMPARATORS_H_

#include "caitlyn/__detail.h"

namespace cait {

template<typename T, typename U>
static constexpr auto cmp_eq(T t, U u) noexcept {
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

template<typename T, typename U>
static constexpr auto cmp_ne(T t, U u) noexcept {
  return !compare_equal(t, u);
}

template<typename T, typename U>
static constexpr auto cmp_less(T t, U u) noexcept {
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

template<typename T, typename U>
static constexpr auto cmp_greater(T t, U u) noexcept {
  return compare_less(u, t);
}

template<typename T, typename U>
static constexpr auto cmp_le(T t, U u) noexcept {
  return !compare_greater(t, u);
}

template<typename T, typename U>
static constexpr auto cmp_ge(T t, U u) noexcept {
  return !compare_less(t, u);
}

}  // namespace cait

#endif  // CAITLYN_CORE_UTILITY_COMPARATORS_COMPARATORS_H_
