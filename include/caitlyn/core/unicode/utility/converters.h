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

#ifndef CAITLYN_CORE_UNICODE_UTILITY_CONVERTERS_H
#define CAITLYN_CORE_UNICODE_UTILITY_CONVERTERS_H

#include <sstream>
#include <tuple>

#include "caitlyn/core/unicode/types/code_point.h"
#include "caitlyn/core/unicode/types/sequence.h"
#include "caitlyn/core/unicode/utility/sequence.h"

namespace cait {

template <typename CharT>
typename char_seq_t<CharT>::type get_char_seq(code_point_t codepoint);

template <>
inline char_seq_t<char_t>::type get_char_seq<char_t>(
    const code_point_t codepoint) {
  const auto length = calculate_char_count(codepoint);
  if (codepoint == 0) {
    return {};
  }
  if (length == 1) {
    return std::make_tuple(static_cast<byte_t>(codepoint),
                           get_char(ascii_t::null), get_char(ascii_t::null),
                           get_char(ascii_t::null));
  }
  if (length == 2) {
    return std::make_tuple(static_cast<byte_t>(0xC0 | (codepoint >> 6)),
                           static_cast<byte_t>(0x80 | (codepoint & 0x3F)),
                           get_char(ascii_t::null), get_char(ascii_t::null));
  }
  if (length == 3) {
    return std::make_tuple(
        static_cast<byte_t>(0xE0 | (codepoint >> 12)),
        static_cast<byte_t>(0x80 | ((codepoint >> 6) & 0x3F)),
        static_cast<byte_t>(0x80 | (codepoint & 0x3F)),
        get_char(ascii_t::null));
  }
  return std::make_tuple(static_cast<byte_t>(0xF0 | (codepoint >> 18)),
                         static_cast<byte_t>(0x80 | ((codepoint >> 12) & 0x3F)),
                         static_cast<byte_t>(0x80 | ((codepoint >> 6) & 0x3F)),
                         static_cast<byte_t>(0x80 | (codepoint & 0x3F)));
}

template <typename CharT>
std::basic_string<CharT> char_to_string(code_point_t code_point);

template <>
inline std::string char_to_string(const code_point_t code_point) {
  std::ostringstream oss;
  const auto seq = get_char_seq<char_t>(code_point);

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
