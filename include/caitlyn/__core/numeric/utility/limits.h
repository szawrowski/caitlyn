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

#ifndef CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_
#define CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_

#include <limits>
#include <utility>

#include "caitlyn/__base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
constexpr T min_value() {
  return std::numeric_limits<T>::min();
}

template <typename T>
constexpr T max_value() {
  return std::numeric_limits<T>::max();
}

template <typename T>
constexpr std::pair<T, T> value_range() {
  return std::make_pair(min_value<T>(), max_value<T>());
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_NUMERIC_UTILITY_LIMITS_H_
