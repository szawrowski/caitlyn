// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_STRING_UNICODE_STRING_H_
#define CAITLYN_CORE_UNICODE_STRING_UNICODE_STRING_H_

#include <string>
#include <vector>

#include "caitlyn/core/containers/defs/container_definitions.h"
#include "caitlyn/core/defs/basic_types.h"
#include "caitlyn/core/string/defs/string_definitions.h"
#include "caitlyn/core/unicode/char/unicode_char.h"

BEGIN_CAITLYN_NS

template <typename CharT>
class unicode_string;

using string_t = unicode_string<char_t>;

template <>
class unicode_string<char_t> {
public:
  using value_type = char_t;
  using data_type = vector_t<value_type>;
  using iterator = data_type::iterator;
  using const_iterator = data_type::const_iterator;
  using size_type = size_t;

public:
  unicode_string() = default;
  unicode_string(const u8char_t* data) { from_chars(data); }
  unicode_string(const std_string_t& data) { from_chars(data); }
  unicode_string(const unicode_string& other) : data_{other.data_} {}
  unicode_string(unicode_string&& other) : data_{std::move(other.data_)} {}

public:
  unicode_string& operator=(const u8char_t* data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const std_string_t& data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const unicode_string& other) = default;

  unicode_string& operator=(unicode_string&& other) noexcept {
    this->data_ = std::move(other.data_);
    return *this;
  }

public:
  [[nodiscard]] const char_t& operator[](const size_type pos) const {
    return data_[pos];
  }

  [[nodiscard]] char_t& operator[](const size_type pos) { return data_[pos]; }

  unicode_string& operator+=(const char_t& c) {
    push_back(c);
    return *this;
  }

public:
  [[nodiscard]] iterator begin() { return {data_.begin()}; }
  [[nodiscard]] iterator end() { return {data_.end()}; }
  [[nodiscard]] const_iterator begin() const { return data_.begin(); }
  [[nodiscard]] const_iterator end() const { return data_.end(); }
  [[nodiscard]] const_iterator cbegin() const { return data_.cbegin(); }
  [[nodiscard]] const_iterator cend() const { return data_.cend(); }

public:
  void append(const char_t& value) { data_.push_back(value); }

  void append(const unicode_string& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

public:
  [[nodiscard]] std_string_t to_std_string() const {
    ostrstream_t oss;
    for (const auto& c : data_) {
      oss << char_to_std_string<u8char_t>(c.get_code_point());
    }
    return oss.str();
  }

public:
  [[nodiscard]] size_type char_count() const { return data_.size(); }

  [[nodiscard]] size_type byte_count() const {
    size_type byte_count{};
    for (const auto& c : data_) {
      byte_count += c.byte_count();
    }
    return byte_count;
  }

public:
  [[nodiscard]] size_type size() const { return data_.size(); }

  [[nodiscard]] size_type length() const { return data_.size(); }

  [[nodiscard]] bool is_empty() const { return data_.empty(); }

  void push_back(const char_t& c) { data_.push_back(c); }

  void pop_back() { data_.pop_back(); }

  void clear() { data_.clear(); }

private:
  void from_chars(const std_string_t& data) {
    const size_type size = data.size();
    data_type ret;

    for (size_type pos = 0; pos < size;) {
      if (pos >= size) {
        break;
      }
      char_t tmp = data.substr(pos).c_str();
      ret.emplace_back(tmp);
      pos += tmp.byte_count();
    }
    data_ = std::move(ret);
  }

private:
  data_type data_;
};

END_CAITLYN_NS

static cait::string_t operator""_str(const cait::u8char_t* str,
                                     const std::size_t) {
  return cait::string_t{str};
}

static cait::bool_t operator==(const cait::string_t& lhs,
                               const cait::string_t& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
  }
  return true;
}

static cait::bool_t operator!=(const cait::string_t& lhs,
                               const cait::string_t& rhs) {
  return !(lhs == rhs);
}

static cait::istream_t& operator>>(cait::istream_t& is, cait::string_t& str) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (is.good()) {
    cait::std_string_t input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static cait::ostream_t& operator<<(cait::ostream_t& os,
                                   const cait::string_t& str) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (os.good()) {
    os << str.to_std_string();
  }
  return os;
}

#endif  // CAITLYN_CORE_UNICODE_STRING_UNICODE_STRING_H_
