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

#ifndef CAITLYN_CORE_CHAR_TYPES_ASCII_H_
#define CAITLYN_CORE_CHAR_TYPES_ASCII_H_

#include "caitlyn/__detail.h"

namespace cait {

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
  latin_cap_letter_a,
  latin_cap_letter_b,
  latin_cap_letter_c,
  latin_cap_letter_d,
  latin_cap_letter_e,
  latin_cap_letter_f,
  latin_cap_letter_g,
  latin_cap_letter_h,
  latin_cap_letter_i,
  latin_cap_letter_j,
  latin_cap_letter_k,
  latin_cap_letter_l,
  latin_cap_letter_m,
  latin_cap_letter_n,
  latin_cap_letter_o,
  latin_cap_letter_p,
  latin_cap_letter_q,
  latin_cap_letter_r,
  latin_cap_letter_s,
  latin_cap_letter_t,
  latin_cap_letter_u,
  latin_cap_letter_v,
  latin_cap_letter_w,
  latin_cap_letter_x,
  latin_cap_letter_y,
  latin_cap_letter_z,
  // ASCII punctuation and symbols
  left_square_br,
  rev_solidus,
  right_square_br,
  circumflex_accent,
  low_line,
  grave_accent,
  // Lowercase Latin alphabet
  latin_small_letter_a,
  latin_small_letter_b,
  latin_small_letter_c,
  latin_small_letter_d,
  latin_small_letter_e,
  latin_small_letter_f,
  latin_small_letter_g,
  latin_small_letter_h,
  latin_small_letter_i,
  latin_small_letter_j,
  latin_small_letter_k,
  latin_small_letter_l,
  latin_small_letter_m,
  latin_small_letter_n,
  latin_small_letter_o,
  latin_small_letter_p,
  latin_small_letter_q,
  latin_small_letter_r,
  latin_small_letter_s,
  latin_small_letter_t,
  latin_small_letter_u,
  latin_small_letter_v,
  latin_small_letter_w,
  latin_small_letter_x,
  latin_small_letter_y,
  latin_small_letter_z,
  // ASCII punctuation and symbols
  left_curly_br,
  vertical_line,
  right_curly_br,
  tilde,
  del
};

}  // namespace cait

#endif  // CAITLYN_CORE_CHAR_TYPES_ASCII_H_
