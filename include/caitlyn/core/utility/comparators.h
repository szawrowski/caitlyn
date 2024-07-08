// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_COMPARATORS_H_
#define CAITLYN_CORE_UTILITY_COMPARATORS_H_

#include "caitlyn/core/core.h"

BEGIN_CAITLYN_NS

template<typename T, typename U>
static constexpr auto cmp_eq(T t, U u) noexcept {
  using UT = std::make_unsigned_t<T>;
  using UU = std::make_unsigned_t<U>;

  if constexpr (std::is_signed_v<T> == std::is_signed_v<U>) {
    return (t == u);
  } else if constexpr (std::is_signed_v<T>) {
    return (t >= 0) && (UT(t) == u);
  } else {
    return (u >= 0) && (t == UU(u));
  }
}

template<typename T, typename U>
static constexpr auto cmp_ne(T t, U u) noexcept {
  return !compare_equal(t, u);
}

template<typename T, typename U>
constexpr auto cmp_less(T t, U u) noexcept {
  using UT = std::make_unsigned_t<T>;
  using UU = std::make_unsigned_t<U>;

  if constexpr (std::is_signed_v<T> == std::is_signed_v<U>) {
    return (t < u);
  } else if constexpr (std::is_signed_v<T>) {
    return (t < 0) || (UT(t) < u);
  } else {
    return (u >= 0) && (t < UU(u));
  }
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

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UTILITY_COMPARATORS_H_
