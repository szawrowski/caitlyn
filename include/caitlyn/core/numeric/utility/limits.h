// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_
#define CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_

#include <limits>

#include "caitlyn/core/utility/types/types.h"

__caitlyn_begin_global_namespace

template <typename T>
static __caitlyn_constexpr T min_value() {
  return std::numeric_limits<T>::min();
}

template <typename T>
static __caitlyn_constexpr T max_value() {
  return std::numeric_limits<T>::max();
}

template <typename T>
static __caitlyn_constexpr pair_t<T, T> value_range() {
  return std::make_pair(min_value<T>(), max_value<T>());
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_
