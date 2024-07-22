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

#ifndef CAITLYN_CORE_STRING_TYPES_STRING_H_
#define CAITLYN_CORE_STRING_TYPES_STRING_H_

#include <algorithm>
#include <iterator>
#include <stdexcept>
#include <string>
#include <utility>

#include "caitlyn/__base.h"
#include "caitlyn/__core/char/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <>
class basic_string_t<char> {
public:
  using value_type = char;
  using char_type = basic_character_t<value_type>;
  using data_type = std::vector<char_type>;
  using basic_string = std::basic_string<value_type>;
  using difference_type = data_type::difference_type;
  using size_type = data_type::size_type;
  using iterator = data_type::iterator;
  using const_iterator = data_type::const_iterator;
  using reverse_iterator = data_type::reverse_iterator;
  using const_reverse_iterator = data_type::const_reverse_iterator;

public:
  // Default constructor
  basic_string_t() = default;

  // Constructor from C-string
  basic_string_t(const char* cstr) {
    while (*cstr) {
      data_.emplace_back(decode_utf8_char(cstr));
      // Move past the current UTF-8 character
      cstr += decode_utf8_char(cstr).size();
    }
  }

  // Constructor from basic_string
  basic_string_t(const basic_string& str) {
    const char* cstr = str.c_str();
    while (*cstr) {
      data_.emplace_back(decode_utf8_char(cstr));
      // Move past the current UTF-8 character
      cstr += decode_utf8_char(cstr).size();
    }
  }

  // Constructor from std::vector<character>
  basic_string_t(const std::vector<char_type>& chars) : data_(chars) {}

  // Constructor from size_type and char
  basic_string_t(const size_type count, const char ch) {
    for (size_type i = 0; i < count; ++i) {
      data_.emplace_back(basic_string(1, ch));
    }
  }

  basic_string_t(const size_type count, const basic_character_t<char>& ch) {
    for (size_type i = 0; i < count; ++i) {
      data_.emplace_back(ch);
    }
  }

  // Constructor from iterator range
  template <typename InputIt>
  basic_string_t(InputIt first, InputIt last) {
    while (first != last) {
      data_.emplace_back(decode_utf8_char(&(*first)));
      ++first;
    }
  }

  // Copy constructor
  basic_string_t(const basic_string_t& other) : data_(other.data_) {}

  // Move constructor
  basic_string_t(basic_string_t&& other) noexcept
      : data_(std::move(other.data_)) {}

  // Copy assignment operator
  basic_string_t& operator=(const basic_string_t& other) {
    if (this != &other) {
      data_ = other.data_;
    }
    return *this;
  }

  // Move assignment operator
  basic_string_t& operator=(basic_string_t&& other) noexcept {
    if (this != &other) {
      data_ = std::move(other.data_);
    }
    return *this;
  }

public:
  // Size
  size_type size() const { return data_.size(); }
  size_type length() const { return data_.size(); }

  // Access character
  const char_type& operator[](const size_type index) const { return data_[index]; }
  char_type& operator[](const size_type index) { return data_[index]; }

  // At method
  const char_type& at(const size_type index) const {
    if (index >= size()) {
      throw std::out_of_range("Index out of range");
    }
    return data_[index];
  }

  char_type& at(const size_type idx) {
    if (idx >= size()) {
      throw std::out_of_range("Index out of range");
    }
    return data_[idx];
  }

public:
  iterator begin() { return data_.begin(); }
  iterator end() { return data_.end(); }
  const_iterator begin() const { return data_.begin(); }
  const_iterator end() const { return data_.end(); }

  reverse_iterator rbegin() { return data_.rbegin(); }
  reverse_iterator rend() { return data_.rend(); }
  const_reverse_iterator rbegin() const { return data_.rbegin(); }
  const_reverse_iterator rend() const { return data_.rend(); }

  const_iterator cbegin() const { return data_.cbegin(); }
  const_iterator cend() const { return data_.cend(); }
  const_reverse_iterator crbegin() const { return data_.crbegin(); }
  const_reverse_iterator crend() const { return data_.crend(); }

public:
  basic_string_t& operator+=(const basic_string_t& str) {
    data_.insert(data_.end(), str.data_.begin(), str.data_.end());
    return *this;
  }

  basic_string_t operator+(const basic_string_t& str) const {
    data_type ret(data_.size() + str.data_.size());
    size_type pos = 0;

    for (; pos < data_.size(); ++pos) {
      ret[pos] = data_[pos];
    }
    for (size_type i = 0; i < str.data_.size(); ++i) {
      ret[pos + i] = str.data_[i];
    }
    return basic_string_t{ret};
  }

  // Append character
  void push_back(const char_type& c) { data_.push_back(c); }

  // Append C-string
  void append(const char* cstr) {
    while (*cstr) {
      data_.emplace_back(decode_utf8_char(cstr));
      // Move past the current UTF-8 character
      cstr += decode_utf8_char(cstr).size();
    }
  }

  // Append C-string
  void append(const size_type count, const char* pattern) {
    size_type i = 0;
    while (i < count) {
      data_.emplace_back(pattern);
      ++i;
    }
  }

  void append(const size_type count, const char_type& pattern) {
    size_type i = 0;
    while (i < count) {
      data_.emplace_back(pattern);
      ++i;
    }
  }

  // Clear
  void clear() { data_.clear(); }


  // Comparison
  bool operator>(const char* other) const { return str() > other; }
  bool operator<(const char* other) const { return str() < other; }
  bool operator>=(const char* other) const { return str() >= other; }
  bool operator<=(const char* other) const { return str() <= other; }
  bool operator==(const char* other) const { return str() == other; }
  bool operator!=(const char* other) const { return str() != other; }

  bool operator>(const basic_string_t& other) const {
    return data_ > other.data_;
  }

  bool operator<(const basic_string_t& other) const {
    return data_ < other.data_;
  }

  bool operator>=(const basic_string_t& other) const {
    return data_ >= other.data_;
  }

  bool operator<=(const basic_string_t& other) const {
    return data_ <= other.data_;
  }

  bool operator==(const basic_string_t& other) const {
    return data_ == other.data_;
  }

  bool operator!=(const basic_string_t& other) const {
    return !(*this == other);
  }

  // Method to check if the string starts with a given prefix
  bool starts_with(const basic_string_t& prefix) const {
    if (prefix.size() > size()) return false;
    return std::equal(prefix.begin(), prefix.end(), data_.begin());
  }

  // Method to check if the string ends with a given suffix
  bool ends_with(const basic_string_t& suffix) const {
    if (suffix.size() > size()) return false;
    return std::equal(suffix.rbegin(), suffix.rend(), data_.rbegin());
  }

  // Method to check if the string contains a given substring
  bool contains(const basic_string_t& substring) const {
    return std::search(data_.begin(), data_.end(), substring.begin(),
                       substring.end()) != data_.end();
  }

  // Method to find the first occurrence of a character
  // size_type find(const char_type& ch, const size_type pos = 0) const {
  //   const auto it = std::find(data_.begin() +
  //   static_cast<difference_type>(pos),
  //                             data_.end(), ch);
  //   return (it != data_.end()) ? std::distance(data_.begin(), it) : npos;
  // }

  // Method to find the first occurrence of a substring
  size_type find(const basic_string_t& substr, const size_type pos = 0) const {
    const auto it =
        std::search(data_.begin() + static_cast<difference_type>(pos),
                    data_.end(), substr.begin(), substr.end());
    return (it != data_.end()) ? std::distance(data_.begin(), it) : npos;
  }

  // Method to find the last occurrence of a character
  // size_type rfind(const char_type& ch, size_type pos = npos) const {
  //   if (pos >= size()) pos = size() - 1;
  //   const auto it = std::find(
  //       data_.rbegin() + static_cast<difference_type>(size() - pos - 1),
  //       data_.rend(), ch);
  //   return (it != data_.rend()) ? size() - 1 - std::distance(data_.rbegin(), it)
  //                               : npos;
  // }

  // Method to find the last occurrence of a substring
  size_type rfind(const basic_string_t& substr, size_type pos = npos) const {
    if (substr.size() > size()) return npos;
    if (pos >= size()) pos = size() - 1;
    const auto it = std::search(
        data_.rbegin() + static_cast<difference_type>(size() - pos - 1),
        data_.rend(), substr.rbegin(), substr.rend());
    return (it != data_.rend()) ? size() - 1 - std::distance(data_.rbegin(), it)
                                : npos;
  }

  // Substring method
  basic_string_t substr(const size_type pos,
                        const size_type count = npos) const {
    if (pos > size()) throw std::out_of_range("Position out of range");
    return basic_string_t{std::vector<char_type>(
        data_.begin() + static_cast<difference_type>(pos),
        data_.begin() +
            static_cast<difference_type>(pos + std::min(count, size() - pos)))};
  }

  // Byte count method
  size_type byte_count() const {
    size_type count = 0;
    for (const auto& ch : data_) {
      count += ch.size();
    }
    return count;
  }

  // Find_if method
  template <typename Predicate>
  size_type find_if(Predicate pred, const size_type pos = 0) const {
    auto it = std::find_if(data_.begin() + static_cast<difference_type>(pos),
                           data_.end(), pred);
    return (it != data_.end()) ? std::distance(data_.begin(), it) : npos;
  }

  // Find_if_not method
  template <typename Predicate>
  size_type find_if_not(Predicate pred, const size_type pos = 0) const {
    auto it = std::find_if_not(
        data_.begin() + static_cast<difference_type>(pos), data_.end(), pred);
    return (it != data_.end()) ? std::distance(data_.begin(), it) : npos;
  }

public:
  bool is_empty() const { return data_.empty(); }
  bool not_empty() const { return !data_.empty(); }

  data_type data() const { return data_; }

  std::basic_string<char> str() const {
    std::ostringstream oss;

    for (const auto& elem : data_) {
      oss << elem.data();
    }
    return oss.str();
  }

  // Insert method
  void insert(const size_type pos, const char* cstr) {
    if (pos > size()) throw std::out_of_range("Position out of range");
    data_type temp_data;
    while (*cstr) {
      temp_data.emplace_back(decode_utf8_char(cstr));
      cstr += decode_utf8_char(cstr).size();
    }
    data_.insert(data_.begin() + static_cast<difference_type>(pos),
                 temp_data.begin(), temp_data.end());
  }

  void insert(const size_type pos, const basic_string_t& str) {
    if (pos > size()) throw std::out_of_range("Position out of range");
    data_.insert(data_.begin() + static_cast<difference_type>(pos),
                 str.data_.begin(), str.data_.end());
  }

  void insert(const size_type pos, const size_type count, const char_type& ch) {
    if (pos > size()) throw std::out_of_range("Position out of range");
    data_.insert(data_.begin() + static_cast<difference_type>(pos), count, ch);
  }

public:
  static constexpr auto npos{static_cast<size_type>(-1)};

private:
  // Helper function to decode a UTF-8 character
  static char_type decode_utf8_char(const char*& cstr) {
    size_type len;
    const unsigned char c = *cstr;

    if ((c & 0x80) == 0) {
      len = 1;
    } else if ((c & 0xE0) == 0xC0) {
      len = 2;
    } else if ((c & 0xF0) == 0xE0) {
      len = 3;
    } else if ((c & 0xF8) == 0xF0) {
      len = 4;
    } else {
      throw std::runtime_error("Invalid UTF-8 sequence");
    }

    return char_type{basic_string(cstr, len)};
  }

private:
  data_type data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is,
                                cait::basic_string_t<char>& str) {
  if (is.good()) {
    std::basic_string<char> input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::basic_string_t<char>& str) {
  os << str.str();
  return os;
}

inline cait::basic_string_t<char> operator""_str(const char* str,
                                                 const std::size_t) {
  return cait::basic_string_t<char>{str};
}

#endif  // CAITLYN_CORE_STRING_TYPES_STRING_H_
