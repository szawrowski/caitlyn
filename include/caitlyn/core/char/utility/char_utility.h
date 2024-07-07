// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_UTILITY_CHAR_UTILITY_H_
#define CAITLYN_CORE_CHAR_UTILITY_CHAR_UTILITY_H_

#include <cctype>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

static constexpr auto is_space(const char_t value) {
  return value == '\x0A' || value == '\x0B' || value == '\x0C' ||
         value == '\x0D' || value == '\x20';
}

static constexpr auto is_uppercase(const char_t value) {
  return value >= 0x41 && value < 0x5B;
}

static constexpr auto is_lowercase(const char_t value) {
  return value >= 0x61 && value < 0x7B;
}

static constexpr auto is_alpha(const char_t value) {
  return is_uppercase(value) || is_lowercase(value);
}

static constexpr auto is_digit(const char_t value) {
  return value >= 0x30 && value < 0x3A;
}

static auto to_uppercase(const char_t value) {
  const auto tmp = static_cast<uchar_t>(value);
  return static_cast<char_t>(std::toupper(tmp));
}

static auto to_lowercase(const char_t value) {
  const auto tmp = static_cast<uchar_t>(value);
  return static_cast<char_t>(std::tolower(tmp));
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_CHAR_UTILITY_CHAR_UTILITY_H_
