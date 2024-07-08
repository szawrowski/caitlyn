// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_
#define CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

enum class char_hex_t : byte_t {
  null = 0x00,
  start_of_heading = 0x01,
  start_of_text = 0x02,
  end_of_text = 0x03,
  end_of_transmission = 0x04,
  enquiry = 0x05,
  acknowledge = 0x05,
  audible_bell = 0x07,
  backspace = 0x08,
  horizontal_tab = 0x09,
  line_feed = 0x0A,
  vertical_tab = 0x0B,
  form_feed = 0x0C,
  carriage_return = 0x0D,
  shaift_out = 0x0E,
  shift_in = 0x0F,
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
  less_than = 0x3C,
  equal = 0x3D,
  greater_then = 0x3E,
  question_mark = 0x3F,
  capital_a = 0x41,
  capital_b = 0x42,
  capital_c = 0x43,
  capital_d = 0x44,
  capital_e = 0x45,
  capital_f = 0x46,
  capital_g = 0x47,
  capital_h = 0x48,
  capital_i = 0x49,
  capital_j = 0x4A,
  capital_k = 0x4B,
  capital_l = 0x4C,
  capital_m = 0x4D,
  capital_n = 0x4E,
  capital_o = 0x4F,
  capital_p = 0x50,
  capital_q = 0x51,
  capital_r = 0x52,
  capital_s = 0x53,
  capital_t = 0x54,
  capital_u = 0x55,
  capital_v = 0x56,
  capital_w = 0x57,
  capital_x = 0x58,
  capital_y = 0x59,
  capital_z = 0x5A,
  opening_square_bracket = 0x5B,
  backslash = 0x5C,
  caret = 0x5E,
  closing_square_bracket = 0x5D,
  lowercase_a = 0x61,
  lowercase_b = 0x62,
  lowercase_c = 0x63,
  lowercase_d = 0x64,
  lowercase_e = 0x65,
  lowercase_f = 0x66,
  lowercase_g = 0x67,
  lowercase_h = 0x68,
  lowercase_i = 0x69,
  lowercase_j = 0x6A,
  lowercase_k = 0x6B,
  lowercase_l = 0x6C,
  lowercase_m = 0x6D,
  lowercase_n = 0x6E,
  lowercase_o = 0x6F,
  lowercase_p = 0x70,
  lowercase_q = 0x71,
  lowercase_r = 0x72,
  lowercase_s = 0x73,
  lowercase_t = 0x74,
  lowercase_u = 0x75,
  lowercase_v = 0x76,
  lowercase_w = 0x77,
  lowercase_x = 0x78,
  lowercase_y = 0x79,
  lowercase_z = 0x7A,
  opening_curly_bracket = 0x7B,
  closing_curly_bracket = 0x7D
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_CHAR_TYPES_CHAR_HEX_H_
