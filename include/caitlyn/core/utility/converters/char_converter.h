// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_CONVERTERS_CHAR_CONVERTER_H_
#define CAITLYN_CORE_UTILITY_CONVERTERS_CHAR_CONVERTER_H_

#include <cctype>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

static constexpr int_t char_to_digit(const stdchar_t value) {
  if (value >= 0x30 && value <= 0x39) {
    return value - 0x30;
  }
  return -1;
}

static constexpr int_t char_to_int(const stdchar_t value) {
  return std::isdigit(value) ? value - 0x30 : std::tolower(value - 0x61) + 0xA;
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UTILITY_CONVERTERS_CHAR_CONVERTER_H_
