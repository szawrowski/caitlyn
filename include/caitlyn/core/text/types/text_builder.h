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

#ifndef CAITLYN_CORE_TEXT_TYPES_TEXT_BUILDER_H_
#define CAITLYN_CORE_TEXT_TYPES_TEXT_BUILDER_H_

#include "caitlyn/core/format.h"
#include "caitlyn/core/string.h"
#include "caitlyn/core/text/types/basic_text_builder.h"

namespace cait {

template <>
class basic_text_builder_t<char> {
public:
  using data_type = std::ostringstream;

public:
  basic_text_builder_t() = default;

  basic_text_builder_t(const char str) { data_ << str; }
  basic_text_builder_t(const char* str) { data_ << str; }
  basic_text_builder_t(const string_t& str) { data_ << str; }

  template <typename... Args>
  basic_text_builder_t(const string_t& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...);
  }

  basic_text_builder_t(const basic_text_builder_t& other)
      : data_{other.data_.str()} {}

  basic_text_builder_t(basic_text_builder_t&& other) noexcept
      : data_{std::move(other.data_)} {}

public:
  void append(const char* str) { data_ << str; }
  void append(const string_t& str) { data_ << str; }

  template <typename... Args>
  void append(const string_t& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...);
  }

  void append_line(const char* str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  void append_line(const string_t& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  template <typename... Args>
  void append_line(const string_t& str, Args&&... args) {
    data_ << format(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
  }

public:
  __caitlyn_nodiscard string_t str() const { return data_.str(); }

private:
  data_type data_;
};

inline basic_text_builder_t<char> make_text() {
  return basic_text_builder_t<char>{};
}

inline basic_text_builder_t<char> make_text(const char c) {
  return basic_text_builder_t<char>{c};
}

inline basic_text_builder_t<char> make_text(const string_t& str) {
  return basic_text_builder_t<char>{str};
}

template <typename... Args>
basic_text_builder_t<char> make_text(const string_t& str, Args&&... args) {
  return basic_text_builder_t<char>{format(str, std::forward<Args>(args)...)};
}

}  // namespace cait

#endif  // CAITLYN_CORE_TEXT_TYPES_TEXT_BUILDER_H_
