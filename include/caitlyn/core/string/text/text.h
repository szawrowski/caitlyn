// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_TEXT_TEXT_H_
#define CAITLYN_CORE_STRING_TEXT_TEXT_H_

#include "caitlyn/core/containers/containers.h"
#include "caitlyn/core/unicode/types/unicode_string.h"

__caitlyn_begin_global_namespace

template <typename CharT>
class text_builder_t;

using text_t = text_builder_t<u8char_t>;
using unitext_t = text_builder_t<unichar_t>;

template <>
class text_builder_t<u8char_t> {
public:
  using data_type = strstream_t;

public:
  text_builder_t() = default;
  text_builder_t(const char_t* str) { data_ << str; }
  text_builder_t(const string_t& str) { data_ << str; }
  text_builder_t(const unichar_t& symbol) { data_ << symbol; }
  text_builder_t(const unistr_t& str) { data_ << str; }

  template <typename... Args>
  text_builder_t(const string_t& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...);
  }

  text_builder_t(const text_builder_t& other) : data_{other.data_.str()} {}
  text_builder_t(text_builder_t&& other) noexcept
      : data_{std::move(other.data_)} {}

public:
  void append(const char_t* str) { data_ << str; }
  void append(const string_t& str) { data_ << str; }
  void append(const unichar_t& symbol) { data_ << symbol; }
  void append(const unistr_t& str) { data_ << str; }

  template <typename... Args>
  void append(const string_t& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...);
  }

  void append_line(const char_t* str) { data_ << str << std::endl; }
  void append_line(const string_t& str) { data_ << str << std::endl; }
  void append_line(const unichar_t& str) { data_ << str << std::endl; }
  void append_line(const unistr_t& str) { data_ << str << std::endl; }

  template <typename... Args>
  void append_line(const string_t& str, Args&&... args) {
    data_ << fmt(str, std::forward<Args>(args)...) << std::endl;
  }

public:
  [[nodiscard]] string_t to_string() const { return data_.str(); }

private:
  data_type data_;
};

template <>
class text_builder_t<unichar_t> {
public:
  using data_type = list_t<unistr_t>;

public:
  text_builder_t() = default;
  text_builder_t(const char_t* str) {
    data_.emplace_back(str);
  }
  text_builder_t(const string_t& str) {
    data_.emplace_back(str);
  }
  text_builder_t(const unichar_t& symbol) {
    data_.emplace_back(char_to_string<u8char_t>(symbol.get_code_point()));
  }
  text_builder_t(const unistr_t& str) {
    data_.emplace_back(str);
  }

  template <typename... Args>
  text_builder_t(const string_t& str, Args&&... args) {
    data_.emplace_back(fmt(str, std::forward<Args>(args)...));
  }

  text_builder_t(const text_builder_t& other) : data_{other.data_} {}
  text_builder_t(text_builder_t&& other) noexcept
      : data_{std::move(other.data_)} {}

public:
  void append(const char_t* str) {
    data_.emplace_back(str);
  }
  void append(const string_t& str) {
    data_.emplace_back(str);
  }
  void append(const unichar_t& symbol) {
    data_.emplace_back(char_to_string<u8char_t>(symbol.get_code_point()));
  }
  void append(const unistr_t& str) {
    data_.emplace_back(str);
  }

  template <typename... Args>
  void append(const string_t& str, Args&&... args) {
    data_.emplace_back(fmt(str, std::forward<Args>(args)...));
  }

  void append_line(const char_t* str) {
    data_.emplace_back(str);
    data_.emplace_back("\n");
  }
  void append_line(const string_t& str) {
    data_.emplace_back(str);
    data_.emplace_back("\n");
  }
  void append_line(const unichar_t& symbol) {
    data_.emplace_back(char_to_string<u8char_t>(symbol.get_code_point()));
    data_.emplace_back("\n");
  }
  void append_line(const unistr_t& str) {
    data_.emplace_back(str);
    data_.emplace_back("\n");
  }

  template <typename... Args>
  void append_line(const string_t& str, Args&&... args) {
    data_.emplace_back(fmt(str, std::forward<Args>(args)...));
    data_.emplace_back("\n");
  }

public:
  [[nodiscard]] string_t to_string() const {
    ostrstream_t oss;
    for (auto& str : data_) {
      oss << str;
    }
    return oss.str();
  }

private:
  data_type data_;
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_STRING_TEXT_TEXT_H_
