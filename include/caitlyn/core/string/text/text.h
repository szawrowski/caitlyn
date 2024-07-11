// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_TEXT_TEXT_H_
#define CAITLYN_CORE_STRING_TEXT_TEXT_H_

#include <list>

#include "caitlyn/core/format/format.h"
#include "caitlyn/core/unicode/unicode.h"

namespace cait {

template <typename CharT>
class text_builder_t;

template <>
class text_builder_t<u8char_t> {
public:
  using data_type = std::ostringstream;

public:
  text_builder_t() = default;

  text_builder_t(const char_t str) { data_ << str; }

  text_builder_t(const char_t* str) { data_ << str; }

  text_builder_t(const std::string& str) { data_ << str; }

  text_builder_t(const unicode_char<u8char_t>& symbol) { data_ << symbol; }

  text_builder_t(const unicode_string<unicode_char<u8char_t>>& str) {
    data_ << str;
  }

  template <typename... Args>
  text_builder_t(const std::string& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...);
  }

  text_builder_t(const text_builder_t& other) : data_{other.data_.str()} {}

  text_builder_t(text_builder_t&& other) noexcept
      : data_{std::move(other.data_)} {}

public:
  void append(const char_t* str) { data_ << str; }

  void append(const std::string& str) { data_ << str; }

  void append(const unicode_char<u8char_t>& symbol) { data_ << symbol; }

  void append(const unicode_string<unicode_char<u8char_t>>& str) {
    data_ << str;
  }

  template <typename... Args>
  void append(const std::string& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...);
  }

  void append_line(const char_t* str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  void append_line(const std::string& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  void append_line(const unicode_char<u8char_t>& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }
  void append_line(const unicode_string<unicode_char<u8char_t>>& str) {
    data_ << str << get_char(ascii_t::line_feed);
  }

  template <typename... Args>
  void append_line(const std::string& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...)
          << get_char(ascii_t::line_feed);
  }

public:
  __caitlyn_nodiscard std::string to_string() const {
    return data_.str();
  }

  __caitlyn_nodiscard unicode_string<unicode_char<u8char_t>> to_unistring()
      const {
    return data_.str();
  }

private:
  data_type data_;
};

static text_builder_t<u8char_t> make_text() {
  return text_builder_t<u8char_t>{};
}

static text_builder_t<u8char_t> make_text(const char_t symbol) {
  return text_builder_t<u8char_t>{symbol};
}

static text_builder_t<u8char_t> make_text(const std::string& str) {
  return text_builder_t<u8char_t>{str};
}

template <typename... Args>
static text_builder_t<u8char_t> make_text(const std::string& str,
                                          Args&&... args) {
  return text_builder_t<u8char_t>{fmt(str, std::forward<Args>(args)...)};
}

static text_builder_t<u8char_t> make_unitext(
    const unicode_char<u8char_t>& str) {
  return text_builder_t<u8char_t>{str.to_string()};
}

static text_builder_t<u8char_t> make_unitext(
    const unicode_string<unicode_char<u8char_t>>& str) {
  return text_builder_t<u8char_t>{str.to_string()};
}

}  // namespace cait

#endif  // CAITLYN_CORE_STRING_TEXT_TEXT_H_
