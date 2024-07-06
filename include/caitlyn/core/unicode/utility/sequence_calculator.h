// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_UTILITY_SEQUENCE_CALCULATOR_H_
#define CAITLYN_CORE_UNICODE_UTILITY_SEQUENCE_CALCULATOR_H_

#include "caitlyn/core/unicode/defs/unicode_types.h"

BEGIN_CAITLYN_NS

template <typename CharT>
static size_t calculate_char_count(code_point_t code_point);

template <>
inline size_t calculate_char_count<u8char_t>(const code_point_t code_point) {
  if (code_point < 0x80) {
    return 1;
  }
  if (code_point < 0x800) {
    return 2;
  }
  if (code_point < 0x10000) {
    return 3;
  }
  return 4;
}

template <>
inline size_t calculate_char_count<u16char_t>(const code_point_t code_point) {
  if (code_point <= 0xFFFF) {
    return 1;
  }
  return 2;
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UNICODE_UTILITY_SEQUENCE_CALCULATOR_H_
