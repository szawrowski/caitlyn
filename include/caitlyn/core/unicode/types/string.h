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

#ifndef CAITLYN_CORE_UNICODE_TYPES_STRING_H_
#define CAITLYN_CORE_UNICODE_TYPES_STRING_H_

#include <vector>

#include "caitlyn/core/unicode/types/char.h"

namespace cait {

template <typename CharT>
class unicode_string;

template <>
class unicode_string<unicode_char<char_t>> {
public:
  using value_type = unicode_char<char_t>;
  using data_type = std::vector<unicode_char<char_t>>;
  using iterator = data_type::iterator;
  using const_iterator = data_type::const_iterator;
  using size_type = size_t;

public:
  unicode_string() = default;
  unicode_string(const char_t data) { from_chars(std::to_string(data)); }
  unicode_string(const char_t* data) { from_chars(data); }
  unicode_string(const std::string& data) { from_chars(data); }
  unicode_string(const unicode_string& other) : data_{other.data_} {}
  unicode_string(unicode_string&& other) : data_{std::move(other.data_)} {}

public:
  unicode_string& operator=(const char_t data) {
    from_chars(std::to_string(data));
    return *this;
  }

  unicode_string& operator=(const char_t* data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const std::string& data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const unicode_string& other) = default;

  unicode_string& operator=(unicode_string&& other) noexcept {
    this->data_ = std::move(other.data_);
    return *this;
  }

public:
  __caitlyn_nodiscard const unicode_char<char_t>& operator[](
      const size_type pos) const {
    return data_[pos];
  }

  __caitlyn_nodiscard unicode_char<char_t>& operator[](const size_type pos) {
    return data_[pos];
  }

  unicode_string& operator+=(const unicode_char<char_t>& c) {
    push_back(c);
    return *this;
  }

public:
  __caitlyn_nodiscard iterator begin() { return {data_.begin()}; }
  __caitlyn_nodiscard iterator end() { return {data_.end()}; }
  __caitlyn_nodiscard const_iterator begin() const { return data_.begin(); }
  __caitlyn_nodiscard const_iterator end() const { return data_.end(); }
  __caitlyn_nodiscard const_iterator cbegin() const { return data_.cbegin(); }
  __caitlyn_nodiscard const_iterator cend() const { return data_.cend(); }

public:
  void append(const unicode_char<char_t>& value) { data_.push_back(value); }

  void append(const unicode_string& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

public:
  __caitlyn_nodiscard std::string to_string() const {
    std::ostringstream oss;
    for (const auto& c : data_) {
      oss << char_to_string<char_t>(c.get_code_point());
    }
    return oss.str();
  }

public:
  __caitlyn_nodiscard size_type char_count() const { return data_.size(); }

  __caitlyn_nodiscard size_type byte_count() const {
    size_type byte_count{};
    for (const auto& c : data_) {
      byte_count += c.byte_count();
    }
    return byte_count;
  }

public:
  __caitlyn_nodiscard size_type size() const { return data_.size(); }
  __caitlyn_nodiscard size_type length() const { return data_.size(); }
  __caitlyn_nodiscard bool_t is_empty() const { return data_.empty(); }

  void push_back(const unicode_char<char_t>& c) { data_.push_back(c); }

  void pop_back() { data_.pop_back(); }

  void clear() { data_.clear(); }

private:
  void from_chars(const std::string& data) {
    const size_type size = data.size();
    data_type ret;

    for (size_type pos = 0; pos < size;) {
      if (pos >= size) {
        break;
      }
      unicode_char<char_t> tmp = data.substr(pos).c_str();
      ret.emplace_back(tmp);
      pos += tmp.byte_count();
    }
    data_ = std::move(ret);
  }

private:
  data_type data_;
};

}  // namespace cait

inline cait::bool_t operator==(
    const cait::unicode_string<cait::unicode_char<cait::char_t>>& lhs,
    const cait::unicode_string<cait::unicode_char<cait::char_t>>& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
  }
  return true;
}

inline cait::bool_t operator!=(
    const cait::unicode_string<cait::unicode_char<cait::char_t>>& lhs,
    const cait::unicode_string<cait::unicode_char<cait::char_t>>& rhs) {
  return !(lhs == rhs);
}

inline std::istream& operator>>(
    std::istream& is,
    cait::unicode_string<cait::unicode_char<cait::char_t>>& str) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

inline std::ostream& operator<<(
    std::ostream& os,
    const cait::unicode_string<cait::unicode_char<cait::char_t>>& str) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (os.good()) {
    for (auto& value : str) {
      os << value;
    }
  }
  return os;
}

inline cait::unicode_string<cait::unicode_char<cait::char_t>> operator""_str(
    const cait::char_t* str, const std::size_t) {
  return cait::unicode_string<cait::unicode_char<cait::char_t>>{str};
}

#endif  // CAITLYN_CORE_UNICODE_TYPES_STRING_H_
