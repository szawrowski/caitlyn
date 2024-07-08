// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CONVERTERS_CHAR_CONVERTERS_H
#define CAITLYN_CORE_UNICODE_CONVERTERS_CHAR_CONVERTERS_H

#include <tuple>

#include "caitlyn/core/unicode/defs/unicode_char_sequence.h"
#include "caitlyn/core/unicode/utility/sequence_calculator.h"

__caitlyn_begin_global_namespace

template <typename CharT>
static typename char_seq_t<CharT>::type get_char_seq(code_point_t codepoint);

template <>
inline char_seq_t<u8char_t>::type get_char_seq<u8char_t>(
    const code_point_t codepoint) {
  const auto length = calculate_char_count<u8char_t>(codepoint);
  if (codepoint == 0) {
    return {};
  }
  if (length == 1) {
    return std::make_tuple(static_cast<u8char_t>(codepoint), 0x0, 0x0, 0x0);
  }
  if (length == 2) {
    return std::make_tuple(static_cast<u8char_t>(0xC0 | (codepoint >> 6)),
                           static_cast<u8char_t>(0x80 | (codepoint & 0x3F)),
                           0x0, 0x0);
  }
  if (length == 3) {
    return std::make_tuple(
        static_cast<u8char_t>(0xE0 | (codepoint >> 12)),
        static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<u8char_t>(0x80 | (codepoint & 0x3F)), 0x0);
  }
  return std::make_tuple(
      static_cast<u8char_t>(0xF0 | (codepoint >> 18)),
      static_cast<u8char_t>(0x80 | ((codepoint >> 12) & 0x3F)),
      static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
      static_cast<u8char_t>(0x80 | (codepoint & 0x3F)));
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_UNICODE_CONVERTERS_CHAR_CONVERTERS_H
