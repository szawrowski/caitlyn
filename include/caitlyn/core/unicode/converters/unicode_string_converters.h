// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H
#define CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H

#include <sstream>

#include "caitlyn/core/unicode/converters/unicode_char_converters.h"

__caitlyn_begin_global_namespace

template <typename CharT>
static std::basic_string<CharT> char_to_string(code_point_t code_point);

template <>
inline string_t char_to_string(const code_point_t code_point) {
  ostrstream_t oss;
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

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_UNICODE_CONVERTERS_STRING_CONVERTERS_H
