// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_
#define CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_

#include <string>

#include "caitlyn/core/unicode/defs/unicode_types.h"

BEGIN_CAITLYN_NS

template <typename CharT>
class unicode_char;

using char_t = unicode_char<u8char_t>;

template <>
class unicode_char<u8char_t> {
public:
  using value_type = u8char_t;
  using char_seq_type = std::basic_string<u8char_t>;
  using code_point_type = code_point_t;
  using size_type = size_t;

public:
  unicode_char() = default;
  unicode_char(const value_type* symbol) { from_chars(symbol); }
  unicode_char(const char_seq_type& symbol) { from_chars(symbol); }
  unicode_char(const code_point_type code_point) : code_point_{code_point} {}

public:
  unicode_char& operator=(const value_type* symbol) {
    from_chars(symbol);
    return *this;
  }

  unicode_char& operator=(const char_seq_type& symbol) {
    from_chars(symbol);
    return *this;
  }

  unicode_char& operator=(const code_point_type code_point) {
    code_point_ = code_point;
    return *this;
  }

public:
  [[nodiscard]] code_point_type get_code_point() const { return code_point_; }
  [[nodiscard]] size_type byte_count() const { return calculate_byte_count(); }

private:
  [[nodiscard]] size_type calculate_byte_count() const {
    if (code_point_ < 0x80) {
      return 1;
    }
    if (code_point_ < 0x800) {
      return 2;
    }
    if (code_point_ < 0x10000) {
      return 3;
    }
    return 4;
  }

  void from_chars(const char_seq_type& seq) {
    const auto lead = static_cast<uchar_t>(seq[0]);
    if ((lead & 0x80) == 0) {
      code_point_ = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      code_point_ = (lead & 0x1F) << 6;
      code_point_ |= static_cast<uchar_t>(seq[1]) & 0x3F;
    } else if ((lead & 0xF0) == 0xE0) {
      code_point_ = (lead & 0x0F) << 12;
      code_point_ |= (static_cast<uchar_t>(seq[1]) & 0x3F) << 6;
      code_point_ |= static_cast<uchar_t>(seq[2]) & 0x3F;
    } else if ((lead & 0xF8) == 0xF0) {
      code_point_ = (lead & 0x07) << 18;
      code_point_ |= (static_cast<uchar_t>(seq[1]) & 0x3F) << 12;
      code_point_ |= (static_cast<uchar_t>(seq[2]) & 0x3F) << 6;
      code_point_ |= static_cast<uchar_t>(seq[3]) & 0x3F;
    } else {
      code_point_ = 0;
    }
  }

private:
  code_point_type code_point_{};
};

END_CAITLYN_NS

static cait::bool_t operator<(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() < rhs.get_code_point();
}

static cait::bool_t operator>(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() > rhs.get_code_point();
}

static cait::bool_t operator<=(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() <= rhs.get_code_point();
}

static cait::bool_t operator>=(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() >= rhs.get_code_point();
}

static cait::bool_t operator==(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() == rhs.get_code_point();
}

static cait::bool_t operator!=(const cait::char_t lhs, const cait::char_t rhs) {
  return lhs.get_code_point() != rhs.get_code_point();
}

#endif  // CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_
