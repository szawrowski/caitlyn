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

#ifndef CAITLYN_CORE_UTILITY_RANDOM_H_
#define CAITLYN_CORE_UTILITY_RANDOM_H_

#include <chrono>
#include <limits>
#include <random>
#include <stdexcept>

#include "caitlyn/__base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
T random(T min = std::numeric_limits<T>::min(),
         T max = std::numeric_limits<T>::max());

template <>
inline int16_t random(const int16_t min, const int16_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<int16_t>{min, max}(engine);
}

template <>
inline uint16_t random(const uint16_t min, const uint16_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<uint16_t>{min, max}(engine);
}

template <>
inline int32_t random(const int32_t min, const int32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<int32_t>{min, max}(engine);
}

template <>
inline uint32_t random(const uint32_t min, const uint32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<uint32_t>{min, max}(engine);
}

template <>
inline int64_t random(const int64_t min, const int64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<int64_t>{min, max}(engine);
}

template <>
inline uint64_t random(const uint64_t min, const uint64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution<uint64_t>{min, max}(engine);
}

template <>
inline float32_t random(const float32_t min, const float32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution<float32_t>{min, max}(engine);
}

template <>
inline float64_t random(const float64_t min, const float64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution<float64_t>{min, max}(engine);
}

template <>
inline floatx_t random(const floatx_t min, const floatx_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution<floatx_t>{min, max}(engine);
}

inline bool random_bool(const double percentage = 0.5) {
  if (percentage < 0.0 || percentage > 1.0) {
    throw std::invalid_argument{"True percentage is only 0.0..1.0"};
  }
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::bernoulli_distribution{percentage}(engine);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_UTILITY_RANDOM_H_
