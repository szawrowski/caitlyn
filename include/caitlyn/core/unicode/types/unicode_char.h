// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CHAR_UNICODE_TYPES_CHAR_H_
#define CAITLYN_CORE_UNICODE_CHAR_UNICODE_TYPES_CHAR_H_

#include <string>

#include "caitlyn/core/io/defs/io_definitions.h"
#include "caitlyn/core/string/defs/string_definitions.h"
#include "caitlyn/core/unicode/converters/unicode_string_converters.h"

BEGIN_CAITLYN_NS

template <typename CharT>
class unicode_char;

using unichar_t = unicode_char<u8char_t>;

template <>
class unicode_char<u8char_t> {
public:
  using value_type = u8char_t;
  using sequence_type = string_t;
  using code_point_type = code_point_t;
  using size_type = size_t;

public:
  unicode_char() = default;
  unicode_char(const value_type* symbol) { from_chars(symbol); }
  unicode_char(const sequence_type& symbol) { from_chars(symbol); }
  unicode_char(const code_point_type code_point) : code_point_{code_point} {}

public:
  unicode_char& operator=(const value_type* symbol) {
    from_chars(symbol);
    return *this;
  }

  unicode_char& operator=(const sequence_type& symbol) {
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
  void from_chars(const sequence_type& seq) {
    code_point_type code_point;
    const auto lead = static_cast<byte_t>(seq[0]);
    if ((lead & 0x80) == 0x0) {
      code_point = lead;
    } else if ((lead & 0xE0) == 0xC0) {
      code_point = (lead & 0x1F) << 6;
      code_point |= static_cast<byte_t>(seq[1]) & 0x3F;
    } else if ((lead & 0xF0) == 0xE0) {
      code_point = (lead & 0x0F) << 12;
      code_point |= (static_cast<byte_t>(seq[1]) & 0x3F) << 6;
      code_point |= static_cast<byte_t>(seq[2]) & 0x3F;
    } else if ((lead & 0xF8) == 0xF0) {
      code_point = (lead & 0x07) << 18;
      code_point |= (static_cast<byte_t>(seq[1]) & 0x3F) << 12;
      code_point |= (static_cast<byte_t>(seq[2]) & 0x3F) << 6;
      code_point |= static_cast<byte_t>(seq[3]) & 0x3F;
    } else {
      code_point = 0x0;
    }
    code_point_ = code_point;
  }

private:
  code_point_type code_point_{};
};

END_CAITLYN_NS

static cait::unichar_t operator""_char(const cait::u8char_t* symbol,
                                       const std::size_t) {
  return cait::unichar_t{symbol};
}

static cait::bool_t operator<(const cait::unichar_t lhs,
                              const cait::unichar_t rhs) {
  return lhs.get_code_point() < rhs.get_code_point();
}

static cait::bool_t operator>(const cait::unichar_t lhs,
                              const cait::unichar_t rhs) {
  return lhs.get_code_point() > rhs.get_code_point();
}

static cait::bool_t operator<=(const cait::unichar_t lhs,
                               const cait::unichar_t rhs) {
  return lhs.get_code_point() <= rhs.get_code_point();
}

static cait::bool_t operator>=(const cait::unichar_t lhs,
                               const cait::unichar_t rhs) {
  return lhs.get_code_point() >= rhs.get_code_point();
}

static cait::bool_t operator==(const cait::unichar_t lhs,
                               const cait::unichar_t rhs) {
  return lhs.get_code_point() == rhs.get_code_point();
}

static cait::bool_t operator!=(const cait::unichar_t lhs,
                               const cait::unichar_t rhs) {
  return lhs.get_code_point() != rhs.get_code_point();
}

static cait::istream_t& operator>>(cait::istream_t& input_stream,
                                   cait::unichar_t& value) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
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

static cait::ostream_t& operator<<(cait::ostream_t& output_stream,
                                   const cait::unichar_t& value) {
#if defined(__caitlyn_windows)
  cait::set_windows_utf8_encode();
#endif
  if (output_stream.good()) {
    output_stream << cait::char_to_std_string<cait::u8char_t>(
        value.get_code_point());
  }
  return output_stream;
}

#endif  // CAITLYN_CORE_UNICODE_CHAR_UNICODE_TYPES_CHAR_H_
