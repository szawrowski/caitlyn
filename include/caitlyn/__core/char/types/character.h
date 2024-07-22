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

#ifndef CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_
#define CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_

#include <iostream>
#include <stdexcept>
#include <string>

#include "caitlyn/__core/char/types/basic_character.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <>
class basic_character_t<char> {
public:
  using value_type = char;
  using data_type = std::string;
  using size_type = data_type::size_type;

public:
  basic_character_t() = default;

  basic_character_t(const char byte) { data_ = byte; }

  basic_character_t(const char* bytes) {
    if (!is_valid_utf8_char(bytes)) {
      throw std::invalid_argument("Invalid UTF-8 character");
    }
    data_ = bytes;
  }

  basic_character_t(const data_type& bytes) {
    if (!is_valid_utf8_char(bytes)) {
      throw std::invalid_argument("Invalid UTF-8 character");
    }
    data_ = bytes;
  }

  basic_character_t& operator=(const char byte) {
    data_ = byte;
    return *this;
  }

  basic_character_t& operator=(const char* bytes) {
    if (!is_valid_utf8_char(bytes)) {
      throw std::invalid_argument("Invalid UTF-8 character");
    }
    data_ = bytes;
    return *this;
  }

  basic_character_t& operator=(const data_type& bytes) {
    if (!is_valid_utf8_char(bytes)) {
      throw std::invalid_argument("Invalid UTF-8 character");
    }
    data_ = bytes;
    return *this;
  }

  size_type size() const { return data_.size(); }
  size_type length() const { return data_.size(); }
  const char* data() const { return data_.data(); }
  const char* c_str() const { return data_.c_str(); }
  const char* str() const { return data_.data(); }

  bool is_empty() const { return data_.empty(); }
  bool not_empty() const { return !data_.empty(); }

  bool operator>(const basic_character_t& other) const {
    return data_ > other.data_;
  }

  bool operator<(const basic_character_t& other) const {
    return data_ < other.data_;
  }

  bool operator>=(const basic_character_t& other) const {
    return data_ >= other.data_;
  }

  bool operator<=(const basic_character_t& other) const {
    return data_ <= other.data_;
  }

  bool operator==(const basic_character_t& other) const {
    return data_ == other.data_;
  }

  bool operator!=(const basic_character_t& other) const {
    return !(*this == other);
  }

private:
  static bool is_valid_utf8_char(const std::string& str) {
    if (str.empty() || str.size() > 4) {
      return false;
    }
    const auto first = static_cast<unsigned char>(str[0]);

    if ((first & 0x80) == 0) {
      return str.size() == 1;
    }
    if ((first & 0xE0) == 0xC0) {
      return str.size() == 2 && is_continuation_byte(str[1]);
    }
    if ((first & 0xF0) == 0xE0) {
      return str.size() == 3 && is_continuation_byte(str[1]) &&
             is_continuation_byte(str[2]);
    }
    if ((first & 0xF8) == 0xF0) {
      return str.size() == 4 && is_continuation_byte(str[1]) &&
             is_continuation_byte(str[2]) && is_continuation_byte(str[3]);
    }
    return false;
  }

  static bool is_continuation_byte(const char c) {
    return (static_cast<unsigned char>(c) & 0xC0) == 0x80;
  }

private:
  data_type data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is,
                                cait::basic_character_t<char>& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::basic_character_t<char>& str) {
  os << str.data();
  return os;
}

inline cait::basic_character_t<char> operator""_char(const char* str,
                                                     const std::size_t) {
  return cait::basic_character_t<char>{str};
}

#endif  // CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_
