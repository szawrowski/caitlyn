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

#ifndef CAITLYN_CORE_UNICODE_TYPES_CHAR_H_
#define CAITLYN_CORE_UNICODE_TYPES_CHAR_H_

#include "caitlyn/core/unicode/utility.h"

namespace cait {

template <typename CharT>
class unicode_char;

template <>
class unicode_char<char> {
public:
  using value_type = char;
  using size_type = size_t;

public:
  unicode_char() = default;
  unicode_char(const value_type symbol) { from_chars(std::to_string(symbol)); }
  unicode_char(const value_type* symbol) { from_chars(symbol); }
  unicode_char(const std::string& symbol) { from_chars(symbol); }
  unicode_char(const code_point_t code_point) : code_point_{code_point} {}

public:
  unicode_char& operator=(const value_type symbol) {
    from_chars(std::to_string(symbol));
    return *this;
  }

  unicode_char& operator=(const value_type* symbol) {
    from_chars(symbol);
    return *this;
  }

  unicode_char& operator=(const std::string& symbol) {
    from_chars(symbol);
    return *this;
  }

  unicode_char& operator=(const code_point_t code_point) {
    code_point_ = code_point;
    return *this;
  }

public:
  __caitlyn_nodiscard code_point_t get_code_point() const {
    return code_point_;
  }

  __caitlyn_nodiscard size_type byte_count() const {
    return calculate_char_count(code_point_);
  }

  __caitlyn_nodiscard std::string to_string() const {
    return char_to_string<char>(code_point_);
  }

private:
  void from_chars(const std::string& seq) {
    code_point_t code_point;
    const auto lead = static_cast<byte_t>(seq[0]);
    if ((lead & 0x80) == 0x0) {
      code_point = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      code_point = (lead & 0x1F) << 6;
      code_point |= static_cast<byte_t>(seq[1]) & 0x3F;
    } else if ((lead & 0xF0) == 0xE0) {
      code_point = (lead & 0x0F) << 12;
      code_point |= (static_cast<byte_t>(seq[1]) & 0x3F) << 6;
      code_point |= static_cast<byte_t>(seq[2]) & 0x3F;
    } else if ((lead & 0xF8) == 0xF0) {
      code_point = (lead & 0x07) << 18;
      code_point |= (static_cast<byte_t>(seq[1]) & 0x3F) << 12;
      code_point |= (static_cast<byte_t>(seq[2]) & 0x3F) << 6;
      code_point |= static_cast<byte_t>(seq[3]) & 0x3F;
    } else {
      code_point = 0x0;
    }
    code_point_ = code_point;
  }

private:
  code_point_t code_point_{};
};

}  // namespace cait

inline bool operator<(const cait::unicode_char<char> lhs,
                      const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() < rhs.get_code_point();
}

inline bool operator>(const cait::unicode_char<char> lhs,
                      const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() > rhs.get_code_point();
}

inline bool operator<=(const cait::unicode_char<char> lhs,
                       const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() <= rhs.get_code_point();
}

inline bool operator>=(const cait::unicode_char<char> lhs,
                       const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() >= rhs.get_code_point();
}

inline bool operator==(const cait::unicode_char<char> lhs,
                       const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() == rhs.get_code_point();
}

inline bool operator!=(const cait::unicode_char<char> lhs,
                       const cait::unicode_char<char> rhs) {
  return lhs.get_code_point() != rhs.get_code_point();
}

inline std::istream& operator>>(std::istream& input_stream,
                                cait::unicode_char<char>& value) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  if (!input_stream.good()) {
    return input_stream;
  }
  char input[4] = {};
  input_stream.get(input[0]);

  if (!input_stream) {
    return input_stream;
  }
  for (size_t i = 1; input[i]; ++i) {
    input_stream.get(input[i]);
    if (!input_stream) {
      return input_stream;
    }
  }
  value = input;
  return input_stream;
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::unicode_char<char>& value) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  if (os.good()) {
    os << value.to_string();
  }
  return os;
}

inline cait::unicode_char<char> operator""_char(const char* symbol,
                                                const std::size_t) {
  return cait::unicode_char<char>{symbol};
}

#endif  // CAITLYN_CORE_UNICODE_TYPES_CHAR_H_
