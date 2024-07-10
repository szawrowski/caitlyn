// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_STRING_UNICODE_TYPES_STRING_H_
#define CAITLYN_CORE_UNICODE_STRING_UNICODE_TYPES_STRING_H_

#include "caitlyn/core/containers/containers.h"
#include "caitlyn/core/unicode/types/unicode_char.h"

__caitlyn_begin_global_namespace

template <typename CharT>
class unicode_string;

using unistr_t = unicode_string<unichar_t>;

template <>
class unicode_string<unichar_t> {
public:
  using value_type = unichar_t;
  using data_type = vector_t<value_type>;
  using iterator = data_type::iterator;
  using const_iterator = data_type::const_iterator;
  using size_type = size_t;

public:
  unicode_string() = default;
  unicode_string(const u8char_t* data) { from_chars(data); }
  unicode_string(const string_t& data) { from_chars(data); }
  unicode_string(const unicode_string& other) : data_{other.data_} {}
  unicode_string(unicode_string&& other) : data_{std::move(other.data_)} {}

public:
  unicode_string& operator=(const u8char_t* data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const string_t& data) {
    from_chars(data);
    return *this;
  }

  unicode_string& operator=(const unicode_string& other) = default;

  unicode_string& operator=(unicode_string&& other) noexcept {
    this->data_ = std::move(other.data_);
    return *this;
  }

public:
  __caitlyn_nodiscard const unichar_t& operator[](const size_type pos) const {
    return data_[pos];
  }

  __caitlyn_nodiscard unichar_t& operator[](const size_type pos) {
    return data_[pos];
  }

  unicode_string& operator+=(const unichar_t& c) {
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
  void append(const unichar_t& value) { data_.push_back(value); }

  void append(const unicode_string& other) {
    data_.insert(data_.end(), other.data_.begin(), other.data_.end());
  }

public:
  __caitlyn_nodiscard string_t to_std_string() const {
    ostrstream_t oss;
    for (const auto& c : data_) {
      oss << char_to_string<u8char_t>(c.get_code_point());
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

  void push_back(const unichar_t& c) { data_.push_back(c); }

  void pop_back() { data_.pop_back(); }

  void clear() { data_.clear(); }

private:
  void from_chars(const string_t& data) {
    const size_type size = data.size();
    data_type ret;

    for (size_type pos = 0; pos < size;) {
      if (pos >= size) {
        break;
      }
      unichar_t tmp = data.substr(pos).c_str();
      ret.emplace_back(tmp);
      pos += tmp.byte_count();
    }
    data_ = std::move(ret);
  }

private:
  data_type data_;
};

__caitlyn_end_global_namespace

static cait::bool_t
operator==(const cait::unistr_t& lhs, const cait::unistr_t& rhs) {
  for (auto lhs_it = lhs.begin(), lhs_end = lhs.end(), rhs_it = rhs.begin(),
            rhs_end = rhs.end();
       lhs_it != lhs_end && rhs_it != rhs_end; ++lhs_it, ++rhs_it) {
    if (*lhs_it != *rhs_it) {
      return {};
    }
  }
  return true;
}

static cait::bool_t operator!=(const cait::unistr_t& lhs,
                               const cait::unistr_t& rhs) {
  return !(lhs == rhs);
}

static cait::istream_t& operator>>(cait::istream_t& is, cait::unistr_t& str) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (is.good()) {
    cait::string_t input;
    std::getline(is, input);
    str = input;
  }
  return is;
}

static cait::ostream_t& operator<<(cait::ostream_t& os,
                                   const cait::unistr_t& str) {
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

static cait::unistr_t operator""_str(const cait::char_t* str,
                                     const std::size_t) {
  return cait::unistr_t{str};
}

#endif  // CAITLYN_CORE_UNICODE_STRING_UNICODE_TYPES_STRING_H_
