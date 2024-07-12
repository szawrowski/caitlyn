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

#ifndef CAITLYN_CORE_CHAR_UTILITY_H_
#define CAITLYN_CORE_CHAR_UTILITY_H_

#include <cctype>

#include "caitlyn/core/char/types.h"

namespace cait {

inline __caitlyn_constexpr14 char_t get_char(const ascii_t value) {
  return static_cast<char_t>(value);
}

inline __caitlyn_constexpr14 bool_t is_space(const char_t value) {
  return value == get_char(ascii_t::line_feed) ||
         value == get_char(ascii_t::line_tab) ||
         value == get_char(ascii_t::form_feed) ||
         value == get_char(ascii_t::carriage_ret) ||
         value == get_char(ascii_t::space);
}

inline __caitlyn_constexpr14 bool_t is_uppercase(const char_t value) {
  return value >= 0x41 && value < 0x5B;
}

inline __caitlyn_constexpr14 bool_t is_lowercase(const char_t value) {
  return value >= 0x61 && value < 0x7B;
}

inline __caitlyn_constexpr14 bool_t is_alpha(const char_t value) {
  return is_uppercase(value) || is_lowercase(value);
}

inline __caitlyn_constexpr14 bool_t is_digit(const char_t value) {
  return value >= 0x30 && value < 0x3A;
}

inline char_t to_uppercase(const char_t value) {
  return static_cast<char_t>(std::toupper(static_cast<uchar_t>(value)));
}

inline char_t to_lowercase(const char_t value) {
  return static_cast<char_t>(std::tolower(static_cast<uchar_t>(value)));
}

inline __caitlyn_constexpr14 int_t char_to_digit(const char_t value) {
  if (value >= 0x30 && value <= 0x39) {
    return value - 0x30;
  }
  return -1;
}

inline constexpr int_t char_to_int(const char_t value) {
  return std::isdigit(value) ? value - 0x30 : std::tolower(value - 0x61) + 0xA;
}

}  // namespace cait

#endif  // CAITLYN_CORE_CHAR_UTILITY_H_
