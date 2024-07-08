// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_RANDOM_H_
#define CAITLYN_CORE_UTILITY_RANDOM_H_

#include <random>

#include "caitlyn/core/core.h"
#include "caitlyn/core/numeric/utility/limits.h"

BEGIN_CAITLYN_NS

template <typename T>
static T random(T min = min_value<T>, T max = max_value<T>);

template <>
inline int16_t random(const int16_t min, const int16_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline uint16_t random(const uint16_t min, const uint16_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline int32_t random(const int32_t min, const int32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline uint32_t random(const uint32_t min, const uint32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline int64_t random(const int64_t min, const int64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline uint64_t random(const uint64_t min, const uint64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_int_distribution{min, max}(engine);
}

template <>
inline float32_t random(const float32_t min, const float32_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution{min, max}(engine);
}

template <>
inline float64_t random(const float64_t min, const float64_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution{min, max}(engine);
}

template <>
inline floatx_t random(const floatx_t min, const floatx_t max) {
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::uniform_real_distribution{min, max}(engine);
}

static bool_t random_bool(const double percentage = 0.5) {
  if (percentage < 0.0 || percentage > 1.0) {
    throw std::invalid_argument{"True percentage is only 0.0..1.0"};
  }
  std::mt19937_64 engine(
      std::chrono::steady_clock::now().time_since_epoch().count());
  return std::bernoulli_distribution{percentage}(engine);
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UTILITY_RANDOM_H_
