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

namespace cait {

template <>
class basic_string_t<char> {
  using value_type = char;
  using data_type = std::basic_string<char>;
  using traits_type = data_type::traits_type;
  using allocator_type = data_type::allocator_type;
  using size_type = data_type::size_type;
  using difference_type = data_type::difference_type;
  using reference = data_type::reference;
  using const_reference = data_type::const_reference;
  using pointer = data_type::pointer;
  using const_pointer = data_type::const_pointer;

  class utf8_char_proxy_t {
  public:
    utf8_char_proxy_t(basic_string_t& str, const size_t pos)
        : str_{str}, pos_{pos} {}

  public:
    utf8_char_proxy_t& operator=(const data_type& utf8_char) {
      str_.replace_utf8_at(pos_, utf8_char);
      return *this;
    }

  public:
    operator const data_type() const { return str_.get_utf8_at(pos_); }

  private:
    basic_string_t& str_;
    size_t pos_;
  };

  class iterator : public std::iterator<std::bidirectional_iterator_tag, char> {
    using base_iterator = data_type::iterator;

  public:
    iterator(const base_iterator current, const base_iterator end)
        : current_{current}, end_{end} {}

    iterator& operator++() {
      if (current_ == end_) return *this;
      do {
        ++current_;
      } while (current_ != end_ && (*current_ & 0xC0) == 0x80);
      return *this;
    }

    iterator operator++(int) {
      const iterator temp = *this;
      ++(*this);
      return temp;
    }

    iterator& operator--() {
      do {
        --current_;
      } while ((*current_ & 0xC0) == 0x80);
      return *this;
    }

    iterator operator--(int) {
      const iterator temp = *this;
      --(*this);
      return temp;
    }

    char& operator*() { return *current_; }
    const char& operator*() const { return *current_; }

    bool operator==(const iterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const iterator& other) const { return !(*this == other); }

  private:
    base_iterator current_;
    base_iterator end_;
  };

  class const_iterator
      : public std::iterator<std::bidirectional_iterator_tag, char> {
    using base_iterator = data_type::const_iterator;

  public:
    const_iterator(const base_iterator current, const base_iterator end)
        : current_{current}, end_{end} {}

    const_iterator& operator++() {
      if (current_ == end_) return *this;
      do {
        ++current_;
      } while (current_ != end_ && (*current_ & 0xC0) == 0x80);
      return *this;
    }

    const_iterator operator++(int) {
      const const_iterator temp = *this;
      ++(*this);
      return temp;
    }

    const_iterator& operator--() {
      do {
        --current_;
      } while ((*current_ & 0xC0) == 0x80);
      return *this;
    }

    const_iterator operator--(int) {
      const const_iterator temp = *this;
      --(*this);
      return temp;
    }

    const char& operator*() const { return *current_; }

    bool operator==(const const_iterator& other) const {
      return current_ == other.current_;
    }
    bool operator!=(const const_iterator& other) const {
      return !(*this == other);
    }

  private:
    base_iterator current_;
    base_iterator end_;
  };

  using reverse_iterator = std::reverse_iterator<iterator>;
  using const_reverse_iterator = std::reverse_iterator<const_iterator>;

public:
  basic_string_t() = default;
  basic_string_t(const char c) : data_{c} {}
  basic_string_t(const char* str) : data_{str} {}
  basic_string_t(data_type str) : data_{std::move(str)} {}

  // template <typename... Args>
  // basic_string_t(const data_type& str, Args&&... args)
  //     : data_{format(str, std::forward<Args>(args)...)} {}

  basic_string_t(const basic_string_t& str) = default;
  basic_string_t(basic_string_t&& str) noexcept : data_{std::move(str.data_)} {}

public:
  basic_string_t& operator=(const char* s) {
    data_ = s;
    return *this;
  }

  basic_string_t& operator=(const data_type& s) {
    data_ = s;
    return *this;
  }

  basic_string_t& operator=(const basic_string_t& str) = default;

  basic_string_t& operator=(basic_string_t&& str) noexcept {
    data_ = std::move(str.data_);
    return *this;
  }

public:
  basic_string_t& operator+=(const basic_string_t& str) {
    data_ += str.data_;
    return *this;
  }

  basic_string_t operator+(const basic_string_t& str) const {
    return {data_ + str.data_};
  }

public:
  size_t size() const { return utf8_char_count(); }
  size_t length() const { return utf8_char_count(); }
  size_t byte_count() const { return data_.size(); }

public:
  bool starts_with(const basic_string_t& prefix) const {
    if (prefix.byte_count() > byte_count()) return false;
    return std::equal(prefix.data_.begin(), prefix.data_.end(), data_.begin());
  }

  bool ends_with(const basic_string_t& suffix) const {
    if (suffix.byte_count() > byte_count()) return false;
    return std::equal(suffix.data_.rbegin(), suffix.data_.rend(),
                      data_.rbegin());
  }

  bool contains(const basic_string_t& str) const { return find(str) != npos; }

public:
  data_type substr(const size_t pos, const size_t len) const {
    if (pos > utf8_char_count())
      throw std::out_of_range{"Position out of range"};

    const auto it = data_.cbegin();
    size_t start_byte_pos = 0;
    for (size_t i = 0; i < pos; ++i) {
      start_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(start_byte_pos));
    }

    size_t end_byte_pos = start_byte_pos;
    for (size_t i = 0; i < len && end_byte_pos < data_.size(); ++i) {
      end_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(end_byte_pos));
    }

    return data_.substr(start_byte_pos, end_byte_pos - start_byte_pos);
  }

  data_type substr(const size_t pos) const {
    return substr(pos, size() - 1);
  }

public:
  data_type str() const { return data_; }
  const char* c_str() const { return data_.c_str(); }
  const data_type& data() const { return data_; }

public:
  void clear() { data_.clear(); }
  bool is_empty() const { return data_.empty(); }

public:
  void push_back(const char* s) { data_.append(s); }
  void push_back(const data_type& s) { data_.append(s); }

  basic_string_t& append(const char* s) {
    data_.append(s);
    return *this;
  }

  basic_string_t& append(const data_type& s) {
    data_.append(s);
    return *this;
  }

  basic_string_t& append(const size_type count, const char pattern) {
    std::ostringstream oss;
    for (size_type i = 0; i < count; ++i) {
      oss << pattern;
    }
    data_.append(oss.str());
    return *this;
  }

  basic_string_t& append(const size_type count, const string_t& pattern) {
    std::ostringstream oss;
    for (size_type i = 0; i < count; ++i) {
      oss << pattern.str();
    }
    data_.append(oss.str());
    return *this;
  }

  basic_string_t& replace(const size_t pos, const size_t len,
                          const basic_string_t& str) {
    if (pos > utf8_char_count())
      throw std::out_of_range{"Position out of range"};

    const auto it = data_.begin();
    size_t start_byte_pos = 0;
    for (size_t i = 0; i < pos; ++i) {
      start_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(start_byte_pos));
    }

    size_t end_byte_pos = start_byte_pos;
    for (size_t i = 0; i < len && end_byte_pos < data_.size(); ++i) {
      end_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(end_byte_pos));
    }

    data_.replace(start_byte_pos, end_byte_pos - start_byte_pos, str.data_);
    return *this;
  }

  basic_string_t& erase(const size_t pos, const size_t len) {
    if (pos > utf8_char_count())
      throw std::out_of_range{"Position out of range"};

    const auto it = data_.begin();
    size_t start_byte_pos = 0;
    for (size_t i = 0; i < pos; ++i) {
      start_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(start_byte_pos));
    }

    size_t end_byte_pos = start_byte_pos;
    for (size_t i = 0; i < len && end_byte_pos < data_.size(); ++i) {
      end_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(end_byte_pos));
    }

    data_.erase(start_byte_pos, end_byte_pos - start_byte_pos);
    return *this;
  }

  basic_string_t& insert(const size_t pos, const basic_string_t& str) {
    if (pos > utf8_char_count())
      throw std::out_of_range{"Position out of range"};

    const auto it = data_.begin();
    size_t start_byte_pos = 0;
    for (size_t i = 0; i < pos; ++i) {
      start_byte_pos +=
          utf8_char_length(it + static_cast<difference_type>(start_byte_pos));
    }

    data_.insert(start_byte_pos, str.data_);
    return *this;
  }

  basic_string_t& insert(const size_t pos, const size_t count,
                         const char pattern) {
    std::ostringstream oss;
    for (size_t i = 0; i < count; ++i) {
      oss << pattern;
    }
    data_.insert(pos, oss.str());
    return *this;
  }

  basic_string_t& insert(const size_t pos, const size_t count,
                         const basic_string_t& pattern) {
    std::ostringstream oss;
    for (size_t i = 0; i < count; ++i) {
      oss << pattern.str();
    }
    data_.insert(pos, oss.str());
    return *this;
  }

  int compare(const basic_string_t& str) const {
    return data_.compare(str.data_);
  }

public:
  size_t find(const basic_string_t& str, const size_t pos = 0) const {
    const auto byte_pos = data_.find(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

  size_t find(const char pattern, const size_t pos = 0) const {
    return find(std::to_string(pattern), pos);
  }

  size_t rfind(const basic_string_t& str, const size_t pos = npos) const {
    const auto byte_pos = data_.rfind(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

  size_t find_first_of(const basic_string_t& str, const size_t pos = 0) const {
    const auto byte_pos =
        data_.find_first_of(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

  size_t find_last_of(const basic_string_t& str,
                      const size_t pos = npos) const {
    const auto byte_pos =
        data_.find_last_of(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

  size_t find_first_not_of(const basic_string_t& str,
                           const size_t pos = 0) const {
    const auto byte_pos =
        data_.find_first_not_of(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

  size_t find_last_not_of(const basic_string_t& str,
                          const size_t pos = npos) const {
    const auto byte_pos =
        data_.find_last_not_of(str.data_, byte_pos_for_char_pos(pos));
    if (byte_pos == npos) {
      return npos;
    }
    return char_pos_for_byte_pos(byte_pos);
  }

public:
  utf8_char_proxy_t at(const size_t pos) {
    return utf8_char_proxy_t{*this, pos};
  }

  data_type at(const size_t pos) const { return get_utf8_at(pos); }

  utf8_char_proxy_t operator[](const size_t pos) {
    return utf8_char_proxy_t{*this, pos};
  }

  data_type operator[](const size_t pos) const { return get_utf8_at(pos); }

  void operator()(const size_t pos, const data_type& utf8_char) {
    replace_utf8_at(pos, utf8_char);
  }

public:
  iterator begin() { return {data_.begin(), data_.end()}; }
  iterator end() { return {data_.end(), data_.end()}; }

  const_iterator begin() const { return {data_.begin(), data_.end()}; }
  const_iterator end() const { return {data_.end(), data_.end()}; }

  reverse_iterator rbegin() { return reverse_iterator{end()}; }
  reverse_iterator rend() { return reverse_iterator{begin()}; }

  const_reverse_iterator rbegin() const {
    return const_reverse_iterator(end());
  }
  const_reverse_iterator rend() const {
    return const_reverse_iterator(begin());
  }

private:
  static size_t utf8_char_length(const data_type::const_iterator& it) {
    if ((*it & 0x80) == 0x00) return 1;  // 0xxxxxxx
    if ((*it & 0xE0) == 0xC0) return 2;  // 110xxxxx
    if ((*it & 0xF0) == 0xE0) return 3;  // 1110xxxx
    if ((*it & 0xF8) == 0xF0) return 4;  // 11110xxx

    throw std::runtime_error{"Invalid UTF-8 encoding"};
  }

  size_t char_pos_for_byte_pos(const size_t byte_pos) const {
    if (byte_pos > data_.size()) {
      throw std::out_of_range{"Byte position out of range"};
    }
    const auto it = data_.cbegin();
    size_t char_pos = 0;

    for (size_t i = 0; i < byte_pos; ++i) {
      if ((*it & 0xC0) != 0x80) {
        ++char_pos;
      }
    }
    return char_pos;
  }

  void replace_utf8_at(const size_t pos, const data_type& utf8_char) {
    if (pos >= utf8_char_count()) {
      throw std::out_of_range{"Index out of range"};
    }
    const size_t byte_pos = byte_pos_for_char_pos(pos);
    const size_t bytes_to_erase = bytes_for_char_at(byte_pos);
    data_.replace(byte_pos, bytes_to_erase, utf8_char);
  }

  data_type get_utf8_at(const size_t pos) const {
    if (pos >= utf8_char_count()) {
      throw std::out_of_range{"Index out of range"};
    }

    const size_t byte_pos = byte_pos_for_char_pos(pos);
    const size_t bytes_to_read = bytes_for_char_at(byte_pos);
    return data_.substr(byte_pos, bytes_to_read);
  }

  size_t utf8_char_count() const {
    size_t count = 0;
    for (const char it : data_) {
      if ((it & 0xC0) != 0x80) {
        ++count;
      }
    }
    return count;
  }

  size_t byte_pos_for_char_pos(const size_t char_pos) const {
    size_t byte_pos = 0;
    size_t count = 0;
    for (auto it = data_.begin(); it != data_.end(); ++it, ++byte_pos) {
      if ((*it & 0xC0) != 0x80) {
        if (count == char_pos) return byte_pos;
        ++count;
      }
    }
    return byte_pos;
  }

  size_t bytes_for_char_at(const size_t byte_pos) const {
    if ((data_[byte_pos] & 0x80) == 0x00) return 1;  // ASCII
    if ((data_[byte_pos] & 0xE0) == 0xC0) return 2;  // 2-byte UTF-8
    if ((data_[byte_pos] & 0xF0) == 0xE0) return 3;  // 3-byte UTF-8
    if ((data_[byte_pos] & 0xF8) == 0xF0) return 4;  // 4-byte UTF-8

    throw std::runtime_error{"Invalid UTF-8 encoding"};
  }

public:
  static constexpr auto npos{static_cast<size_type>(-1)};

private:
  data_type data_{};
};

}  // namespace cait

inline bool operator==(const cait::basic_string_t<char>& lhs,
                       const char rhs) {
  return lhs.data() == std::to_string(rhs);
}

inline bool operator!=(const cait::basic_string_t<char>& lhs,
                       const char rhs) {
  return lhs.data() != std::to_string(rhs);
}

inline bool operator==(const cait::basic_string_t<char>& lhs,
                       const cait::basic_string_t<char>& rhs) {
  return lhs.data() == rhs.data();
}

inline bool operator!=(const cait::basic_string_t<char>& lhs,
                       const cait::basic_string_t<char>& rhs) {
  return lhs.data() != rhs.data();
}

inline bool operator<(const cait::basic_string_t<char>& lhs,
                      const cait::basic_string_t<char>& rhs) {
  return lhs.data() < rhs.data();
}

inline bool operator<=(const cait::basic_string_t<char>& lhs,
                       const cait::basic_string_t<char>& rhs) {
  return lhs.data() <= rhs.data();
}

inline bool operator>(const cait::basic_string_t<char>& lhs,
                      const cait::basic_string_t<char>& rhs) {
  return lhs.data() > rhs.data();
}

inline bool operator>=(const cait::basic_string_t<char>& lhs,
                       const cait::basic_string_t<char>& rhs) {
  return lhs.data() >= rhs.data();
}

inline std::istream& operator>>(std::istream& is,
                                cait::basic_string_t<char>& str) {
  if (is.good()) {
    std::string input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::basic_string_t<char>& str) {
  if (os.good()) {
    os << str.str();
  }
  return os;
}

inline cait::basic_string_t<char> operator""_str(const char* str,
                                                 const std::size_t) {
  return cait::basic_string_t<char>{str};
}

#endif  // CAITLYN_CORE_STRING_TYPES_STRING_H_
