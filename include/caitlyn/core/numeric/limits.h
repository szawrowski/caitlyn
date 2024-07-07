// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_NUMERIC_LIMITS_H_
#define CAITLYN_CORE_NUMERIC_LIMITS_H_

#include <limits>
#include <utility>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename T>
static constexpr auto min_value = typename std::numeric_limits<T>::min;

template <typename T>
static constexpr auto max_value = typename std::numeric_limits<T>::max;

template<typename T>
static constexpr std::pair<T, T> value_range() {
  return std::make_pair(min_value<T>(), max_value<T>());
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_NUMERIC_LIMITS_H_