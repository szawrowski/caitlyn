// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_
#define CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

enum class char_hex_t : byte_t {
  audible_bell = 0x07,
  backspace = 0x08,
  horizontal_tab = 0x09,
  line_feed = 0x0A,
  vertical_tab = 0x0B,
  form_feed = 0x0C,
  carriage_return = 0x0D,
  space = 0x20,
  double_quote = 0x22,
  single_quote = 0x27,
  plus = 0x2B,
  comma = 0x2C,
  minus = 0x2D,
  point = 0x2E,
  slash = 0x2F,
  colon = 0x3A,
  semicolon = 0x3B,
  question_mark = 0x3F,
  capital_e = 0x45,
  opening_square_bracket = 0x5B,
  backslash = 0x5C,
  closing_square_bracket = 0x5D,
  lowercase_a = 0x61,
  lowercase_b = 0x62,
  lowercase_e = 0x65,
  lowercase_f = 0x66,
  lowercase_n = 0x6E,
  lowercase_r = 0x72,
  lowercase_t = 0x74,
  lowercase_u = 0x75,
  lowercase_v = 0x76,
  opening_curly_bracket = 0x7B,
  closing_curly_bracket = 0x7D
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_
