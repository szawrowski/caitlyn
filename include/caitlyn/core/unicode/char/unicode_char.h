// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_
#define CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_

#include <string>

#include "caitlyn/core/unicode/converters/unicode_string_converters.h"

#if defined(__caitlyn_windows)
  #include <windows.h>
#endif

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

  [[nodiscard]] size_type byte_count() const {
    return calculate_char_count<u8char_t>(code_point_);
  }

private:
  void from_chars(const char_seq_type& seq) {
    code_point_type code_point;
    const auto lead = static_cast<uchar_t>(seq[0]);

    if ((lead & 0x80) == 0x0) {
      code_point = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      code_point = (lead & 0x1F) << 6;
      code_point |= static_cast<uchar_t>(seq[1]) & 0x3F;
    } else if ((lead & 0xF0) == 0xE0) {
      code_point = (lead & 0x0F) << 12;
      code_point |= (static_cast<uchar_t>(seq[1]) & 0x3F) << 6;
      code_point |= static_cast<uchar_t>(seq[2]) & 0x3F;
    } else if ((lead & 0xF8) == 0xF0) {
      code_point = (lead & 0x07) << 18;
      code_point |= (static_cast<uchar_t>(seq[1]) & 0x3F) << 12;
      code_point |= (static_cast<uchar_t>(seq[2]) & 0x3F) << 6;
      code_point |= static_cast<uchar_t>(seq[3]) & 0x3F;
    } else {
      code_point = 0x0;
    }
    code_point_ = code_point;
  }

private:
  code_point_type code_point_{};
};

END_CAITLYN_NS

static cait::char_t operator""_char(const cait::u8char_t* symbol,
                                    const std::size_t) {
  return cait::char_t{symbol};
}

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

static std::basic_istream<cait::u8char_t>& operator>>(
    std::basic_istream<cait::u8char_t>& input_stream, cait::char_t& value) {
#if defined(__caitlyn_windows)
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
  if (!input_stream.good()) {
    return input_stream;
  }
  cait::u8char_t input[4] = {};
  input_stream.get(input[0]);

  if (!input_stream) {
    return input_stream;
  }
  for (cait::size_t i = 1; input[i]; ++i) {
    input_stream.get(input[i]);
    if (!input_stream) {
      return input_stream;
    }
  }
  value = input;
  return input_stream;
}

static std::basic_ostream<cait::u8char_t>& operator<<(
    std::basic_ostream<cait::u8char_t>& output_stream,
    const cait::char_t& value) {
#if defined(__caitlyn_windows)
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif
  if (output_stream.good()) {
    output_stream << cait::char_to_std_string<cait::u8char_t>(
        value.get_code_point());
  }
  return output_stream;
}

#endif  // CAITLYN_CORE_UNICODE_CHAR_UNICODE_CHAR_H_
