// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H
#define CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H

#include <sstream>

#include "caitlyn/core/unicode/converters/unicode_char_converters.h"

BEGIN_CAITLYN_NS

template <typename CharT>
static std::basic_string<CharT> char_to_std_string(code_point_t code_point);

template <>
inline std::basic_string<u8char_t> char_to_std_string(
    const code_point_t code_point) {
  std::basic_ostringstream<u8char_t> oss;
  const auto [first, second, third, fourth] =
      get_char_seq<u8char_t>(code_point);

  oss << first;
  if (second) {
    oss << second;
  }
  if (third) {
    oss << third;
  }
  if (fourth) {
    oss << fourth;
  }
  return oss.str();
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H
