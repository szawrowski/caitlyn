// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_UTILITY_UTILITY_H_
#define CAITLYN_CORE_CHAR_UTILITY_UTILITY_H_

#include <cctype>

#include "caitlyn/core/char/types/types.h"

__caitlyn_begin_global_namespace

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

static constexpr char_t get_char(const ascii_t value) {
  return static_cast<char_t>(value);
}

static constexpr int_t char_to_digit(const char_t value) {
  if (value >= 0x30 && value <= 0x39) {
    return value - 0x30;
  }
  return -1;
}

static constexpr int_t char_to_int(const char_t value) {
  return std::isdigit(value) ? value - 0x30 : std::tolower(value - 0x61) + 0xA;
}

static constexpr char_t end_line() {
  return get_char(ascii_t::line_feed);
}

static constexpr char_t end_str() {
  return get_char(ascii_t::null);
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_CHAR_UTILITY_UTILITY_H_
