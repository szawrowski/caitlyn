// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_TYPES_ASCII_H_
#define CAITLYN_CORE_CHAR_TYPES_ASCII_H_

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

enum class ascii_t : byte_t {
  // C0 controls
  null = 0x00,
  start_of_heading,
  start_of_text,
  end_of_text,
  end_of_trans,
  enquiry,
  ack,
  bell,
  backspace,
  char_tab,
  line_feed,
  line_tab,
  form_feed,
  carriage_ret,
  shift_out,
  shift_in,
  data_link_esc,
  device_ctrl_one,
  device_ctrl_two,
  device_ctrl_three,
  device_ctrl_four,
  negative_ack,
  sync_idle,
  end_of_trans_block,
  cancel,
  end_of_medium,
  substitute,
  escape,
  info_sep_one,
  info_sep_two,
  info_sep_three,
  info_sep_four,
  // ASCII punctuation and symbols
  space,
  excl_mark,
  quot_mark,
  number_sign,
  dollar_sign,
  percent_sign,
  ampersand,
  apostrophe,
  left_paren,
  right_paren,
  asterisk,
  // ASCII math operator
  plus_sign,
  // ASCII punctuation
  comma,
  hyphen_minus,
  full_stop,
  solidus,
  // ASCII digits
  digit_zero,
  digit_one,
  digit_two,
  digit_three,
  digit_four,
  digit_five,
  digit_six,
  digit_seven,
  digit_eight,
  digit_nine,
  // ASCII punctuation
  colon,
  semicolon,
  // ASCII mathematical operators
  less_than_sign,
  equals_sign,
  greater_than_sign,
  // ASCII punctuation
  quest_mark,
  commercial_at,
  // Uppercase Latin alphabet
  latin_cap_lett_a,
  latin_cap_lett_b,
  latin_cap_lett_c,
  latin_cap_lett_d,
  latin_cap_lett_e,
  latin_cap_lett_f,
  latin_cap_lett_g,
  latin_cap_lett_h,
  latin_cap_lett_i,
  latin_cap_lett_j,
  latin_cap_lett_k,
  latin_cap_lett_l,
  latin_cap_lett_m,
  latin_cap_lett_n,
  latin_cap_lett_o,
  latin_cap_lett_p,
  latin_cap_lett_q,
  latin_cap_lett_r,
  latin_cap_lett_s,
  latin_cap_lett_t,
  latin_cap_lett_u,
  latin_cap_lett_v,
  latin_cap_lett_w,
  latin_cap_lett_x,
  latin_cap_lett_y,
  latin_cap_lett_z,
  // ASCII punctuation and symbols
  left_square_br,
  rev_solidus,
  right_square_br,
  circumflex_accent,
  low_line,
  grave_accent,
  // Lowercase Latin alphabet
  latin_small_lett_a,
  latin_small_lett_b,
  latin_small_lett_c,
  latin_small_lett_d,
  latin_small_lett_e,
  latin_small_lett_f,
  latin_small_lett_g,
  latin_small_lett_h,
  latin_small_lett_i,
  latin_small_lett_j,
  latin_small_lett_k,
  latin_small_lett_l,
  latin_small_lett_m,
  latin_small_lett_n,
  latin_small_lett_o,
  latin_small_lett_p,
  latin_small_lett_q,
  latin_small_lett_r,
  latin_small_lett_s,
  latin_small_lett_t,
  latin_small_lett_u,
  latin_small_lett_v,
  latin_small_lett_w,
  latin_small_lett_x,
  latin_small_lett_y,
  latin_small_lett_z,
  // ASCII punctuation and symbols
  left_curly_br ,
  vertical_line ,
  right_curly_br ,
  tilde ,
  del
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_CHAR_TYPES_ASCII_H_
