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

#ifndef CAITLYN_CORE_TEXT_TEXT_BUILDER_H_
#define CAITLYN_CORE_TEXT_TEXT_BUILDER_H_

#include "caitlyn/core/format.h"
#include "caitlyn/core/unicode.h"

namespace cait {

template <typename CharT>
class text_builder_t;

template <>
class text_builder_t<char> {
public:
  using data_type = std::ostringstream;

public:
  text_builder_t() = default;

  text_builder_t(const char str) { data_ << str; }

  text_builder_t(const char* str) { data_ << str; }

  text_builder_t(const std::string& str) { data_ << str; }

  text_builder_t(const unicode_char<char>& symbol) { data_ << symbol; }

  text_builder_t(const unicode_string<unicode_char<char>>& str) {
    data_ << str;
  }

  template <typename... Args>
  text_builder_t(const std::string& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...);
  }

  text_builder_t(const text_builder_t& other) : data_{other.data_.str()} {}

  text_builder_t(text_builder_t&& other) noexcept
      : data_{std::move(other.data_)} {}

public:
  void append(const char* str) { data_ << str; }

  void append(const std::string& str) { data_ << str; }

  void append(const unicode_char<char>& symbol) { data_ << symbol; }

  void append(const unicode_string<unicode_char<char>>& str) { data_ << str; }

  template <typename... Args>
  void append(const std::string& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...);
  }

  void append_line(const char* str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  void append_line(const std::string& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  void append_line(const unicode_char<char>& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }
  void append_line(const unicode_string<unicode_char<char>>& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  template <typename... Args>
  void append_line(const std::string& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
  }

public:
  __caitlyn_nodiscard std::string to_string() const { return data_.str(); }

  __caitlyn_nodiscard unicode_string<unicode_char<char>> to_unistring() const {
    return data_.str();
  }

private:
  data_type data_;
};

inline text_builder_t<char> make_text() { return text_builder_t<char>{}; }

inline text_builder_t<char> make_text(const char symbol) {
  return text_builder_t<char>{symbol};
}

inline text_builder_t<char> make_text(const std::string& str) {
  return text_builder_t<char>{str};
}

template <typename... Args>
text_builder_t<char> make_text(const std::string& str, Args&&... args) {
  return text_builder_t<char>{format(str, std::forward<Args>(args)...)};
}

inline text_builder_t<char> make_unitext(const unicode_char<char>& str) {
  return text_builder_t<char>{str.to_string()};
}

inline text_builder_t<char> make_unitext(
    const unicode_string<unicode_char<char>>& str) {
  return text_builder_t<char>{str.to_string()};
}

}  // namespace cait

#endif  // CAITLYN_CORE_TEXT_TEXT_BUILDER_H_
