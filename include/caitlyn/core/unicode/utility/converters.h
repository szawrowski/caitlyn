// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_UTILITY_CONVERTERS_H
#define CAITLYN_CORE_UNICODE_UTILITY_CONVERTERS_H

#include <sstream>
#include <tuple>

#include "caitlyn/core/unicode/types/unicode_char_sequence.h"
#include "caitlyn/core/unicode/utility/sequence_calculator.h"

namespace cait {

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
    return std::make_tuple(static_cast<u8char_t>(codepoint),
                           get_char(ascii_t::null), get_char(ascii_t::null),
                           get_char(ascii_t::null));
  }
  if (length == 2) {
    return std::make_tuple(static_cast<u8char_t>(0xC0 | (codepoint >> 6)),
                           static_cast<u8char_t>(0x80 | (codepoint & 0x3F)),
                           get_char(ascii_t::null), get_char(ascii_t::null));
  }
  if (length == 3) {
    return std::make_tuple(
        static_cast<u8char_t>(0xE0 | (codepoint >> 12)),
        static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<u8char_t>(0x80 | (codepoint & 0x3F)),
        get_char(ascii_t::null));
  }
  return std::make_tuple(
      static_cast<u8char_t>(0xF0 | (codepoint >> 18)),
      static_cast<u8char_t>(0x80 | ((codepoint >> 12) & 0x3F)),
      static_cast<u8char_t>(0x80 | ((codepoint >> 6) & 0x3F)),
      static_cast<u8char_t>(0x80 | (codepoint & 0x3F)));
}

template <typename CharT>
static std::basic_string<CharT> char_to_string(code_point_t code_point);

template <>
inline std::string char_to_string(const code_point_t code_point) {
  std::ostringstream oss;
  const auto seq = get_char_seq<u8char_t>(code_point);

  oss << std::get<0>(seq);
  if (std::get<1>(seq)) {
    oss << std::get<1>(seq);
  }
  if (std::get<2>(seq)) {
    oss << std::get<2>(seq);
  }
  if (std::get<3>(seq)) {
    oss << std::get<3>(seq);
  }
  return oss.str();
}

}  // namespace cait

#endif  // CAITLYN_CORE_UNICODE_UTILITY_CONVERTERS_H
