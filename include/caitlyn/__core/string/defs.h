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

#ifndef CAITLYN_CORE_STRING_DEFS_H_
#define CAITLYN_CORE_STRING_DEFS_H_

#include "caitlyn/__base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_DEF_NAMESPACE_BEGIN

constexpr auto empty = "";  // Empty string

constexpr auto null = "\x00";                       // NULL
constexpr auto start_of_heading = "\x01";           // START OF HEADING
constexpr auto start_of_text = "\x02";              // START OF TEXT
constexpr auto end_of_text = "\x03";                // END OF TEXT
constexpr auto end_of_transmission = "\x04";        // END OF TRANSMISSION
constexpr auto enquiry = "\x05";                    // ENQUIRY
constexpr auto acknowledge = "\x06";                // ACKNOWLEDGE
constexpr auto bell = "\x07";                       // BELL
constexpr auto backspace = "\x08";                  // BACKSPACE
constexpr auto character_tabulation = "\x09";       // CHARACTER TABULATION
constexpr auto line_feed = "\x0A";                  // LINE FEED (LF)
constexpr auto line_tabulation = "\x0B";            // LINE TABULATION
constexpr auto form_feed = "\x0C";                  // FORM FEED (FF)
constexpr auto carriage_return = "\x0D";            // CARRIAGE RETURN (CR)
constexpr auto shift_out = "\x0E";                  // SHIFT OUT
constexpr auto shift_in = "\x0F";                   // SHIFT IN
constexpr auto data_link_escape = "\x10";           // DATA LINK ESCAPE
constexpr auto device_control_one = "\x11";         // DEVICE CONTROL ONE
constexpr auto device_control_two = "\x12";         // DEVICE CONTROL TWO
constexpr auto device_control_three = "\x13";       // DEVICE CONTROL THREE
constexpr auto device_control_four = "\x14";        // DEVICE CONTROL FOUR
constexpr auto negative_acknowledge = "\x15";       // NEGATIVE ACKNOWLEDGE
constexpr auto synchronous_idle = "\x16";           // SYNCHRONOUS IDLE
constexpr auto end_of_transmission_block = "\x17";  // END OF TRANSMISSION BLOCK
constexpr auto cancel = "\x18";                     // CANCEL
constexpr auto end_of_medium = "\x19";              // END OF MEDIUM
constexpr auto substitute = "\x1A";                 // SUBSTITUTE
constexpr auto escape = "\x1B";                     // ESCAPE
constexpr auto information_separator_four =
    "\x1C";  // INFORMATION SEPARATOR FOUR
constexpr auto information_separator_three =
    "\x1D";  // INFORMATION SEPARATOR THREE
constexpr auto information_separator_two = "\x1E";  // INFORMATION SEPARATOR TWO
constexpr auto information_separator_one = "\x1F";  // INFORMATION SEPARATOR ONE
constexpr auto space = "\x20";                      // SPACE
constexpr auto exclamation_mark = "\x21";           // EXCLAMATION MARK
constexpr auto quotation_mark = "\x22";             // QUOTATION MARK
constexpr auto number_sign = "\x23";                // NUMBER SIGN
constexpr auto dollar_sign = "\x24";                // DOLLAR SIGN
constexpr auto percent_sign = "\x25";               // PERCENT SIGN
constexpr auto ampersand = "\x26";                  // AMPERSAND
constexpr auto apostrophe = "\x27";                 // APOSTROPHE
constexpr auto left_parenthesis = "\x28";           // LEFT PARENTHESIS
constexpr auto right_parenthesis = "\x29";          // RIGHT PARENTHESIS
constexpr auto asterisk = "\x2A";                   // ASTERISK
constexpr auto plus_sign = "\x2B";                  // PLUS SIGN
constexpr auto comma = "\x2C";                      // COMMA
constexpr auto hyphen_minus = "\x2D";               // HYPHEN-MINUS
constexpr auto full_stop = "\x2E";                  // FULL STOP
constexpr auto solidus = "\x2F";                    // SOLIDUS
constexpr auto digit_zero = "\x30";                 // DIGIT ZERO
constexpr auto digit_one = "\x31";                  // DIGIT ONE
constexpr auto digit_two = "\x32";                  // DIGIT TWO
constexpr auto digit_three = "\x33";                // DIGIT THREE
constexpr auto digit_four = "\x34";                 // DIGIT FOUR
constexpr auto digit_five = "\x35";                 // DIGIT FIVE
constexpr auto digit_six = "\x36";                  // DIGIT SIX
constexpr auto digit_seven = "\x37";                // DIGIT SEVEN
constexpr auto digit_eight = "\x38";                // DIGIT EIGHT
constexpr auto digit_nine = "\x39";                 // DIGIT NINE
constexpr auto colon = "\x3A";                      // COLON
constexpr auto semicolon = "\x3B";                  // SEMICOLON
constexpr auto less_than_sign = "\x3C";             // LESS-THAN SIGN
constexpr auto equals_sign = "\x3D";                // EQUALS SIGN
constexpr auto greater_than_sign = "\x3E";          // GREATER-THAN SIGN
constexpr auto question_mark = "\x3F";              // QUESTION MARK
constexpr auto commercial_at = "\x40";              // COMMERCIAL AT
constexpr auto latin_capital_letter_a = "\x41";     // LATIN CAPITAL LETTER A
constexpr auto latin_capital_letter_b = "\x42";     // LATIN CAPITAL LETTER B
constexpr auto latin_capital_letter_c = "\x43";     // LATIN CAPITAL LETTER C
constexpr auto latin_capital_letter_d = "\x44";     // LATIN CAPITAL LETTER D
constexpr auto latin_capital_letter_e = "\x45";     // LATIN CAPITAL LETTER E
constexpr auto latin_capital_letter_f = "\x46";     // LATIN CAPITAL LETTER F
constexpr auto latin_capital_letter_g = "\x47";     // LATIN CAPITAL LETTER G
constexpr auto latin_capital_letter_h = "\x48";     // LATIN CAPITAL LETTER H
constexpr auto latin_capital_letter_i = "\x49";     // LATIN CAPITAL LETTER I
constexpr auto latin_capital_letter_j = "\x4A";     // LATIN CAPITAL LETTER J
constexpr auto latin_capital_letter_l = "\x4C";     // LATIN CAPITAL LETTER L
constexpr auto latin_capital_letter_m = "\x4D";     // LATIN CAPITAL LETTER M
constexpr auto latin_capital_letter_n = "\x4E";     // LATIN CAPITAL LETTER N
constexpr auto latin_capital_letter_o = "\x4F";     // LATIN CAPITAL LETTER O
constexpr auto latin_capital_letter_p = "\x50";     // LATIN CAPITAL LETTER P
constexpr auto latin_capital_letter_q = "\x51";     // LATIN CAPITAL LETTER Q
constexpr auto latin_capital_letter_r = "\x52";     // LATIN CAPITAL LETTER R
constexpr auto latin_capital_letter_s = "\x53";     // LATIN CAPITAL LETTER S
constexpr auto latin_capital_letter_t = "\x54";     // LATIN CAPITAL LETTER T
constexpr auto latin_capital_letter_u = "\x55";     // LATIN CAPITAL LETTER U
constexpr auto latin_capital_letter_v = "\x56";     // LATIN CAPITAL LETTER V
constexpr auto latin_capital_letter_w = "\x57";     // LATIN CAPITAL LETTER W
constexpr auto latin_capital_letter_x = "\x58";     // LATIN CAPITAL LETTER X
constexpr auto latin_capital_letter_y = "\x59";     // LATIN CAPITAL LETTER Y
constexpr auto latin_capital_letter_z = "\x5A";     // LATIN CAPITAL LETTER Z
constexpr auto left_square_bracket = "\x5B";        // LEFT SQUARE BRACKET
constexpr auto reverse_solidus = "\x5C";            // REVERSE SOLIDUS
constexpr auto right_square_bracket = "\x5D";       // RIGHT SQUARE BRACKET
constexpr auto circumflex_accent = "\x5E";          // CIRCUMFLEX ACCENT
constexpr auto low_line = "\x5F";                   // LOW LINE
constexpr auto grave_accent = "\x60";               // GRAVE ACCENT
constexpr auto latin_small_letter_a = "\x61";       // LATIN SMALL LETTER A
constexpr auto latin_small_letter_b = "\x62";       // LATIN SMALL LETTER B
constexpr auto latin_small_letter_c = "\x63";       // LATIN SMALL LETTER C
constexpr auto latin_small_letter_d = "\x64";       // LATIN SMALL LETTER D
constexpr auto latin_small_letter_e = "\x65";       // LATIN SMALL LETTER E
constexpr auto latin_small_letter_f = "\x66";       // LATIN SMALL LETTER F
constexpr auto latin_small_letter_g = "\x67";       // LATIN SMALL LETTER G
constexpr auto latin_small_letter_h = "\x68";       // LATIN SMALL LETTER H
constexpr auto latin_small_letter_i = "\x69";       // LATIN SMALL LETTER I
constexpr auto latin_small_letter_j = "\x6A";       // LATIN SMALL LETTER J
constexpr auto latin_small_letter_l = "\x6C";       // LATIN SMALL LETTER L
constexpr auto latin_small_letter_m = "\x6D";       // LATIN SMALL LETTER M
constexpr auto latin_small_letter_n = "\x6E";       // LATIN SMALL LETTER N
constexpr auto latin_small_letter_o = "\x6F";       // LATIN SMALL LETTER O
constexpr auto latin_small_letter_p = "\x70";       // LATIN SMALL LETTER P
constexpr auto latin_small_letter_q = "\x71";       // LATIN SMALL LETTER Q
constexpr auto latin_small_letter_r = "\x72";       // LATIN SMALL LETTER R
constexpr auto latin_small_letter_s = "\x73";       // LATIN SMALL LETTER S
constexpr auto latin_small_letter_t = "\x74";       // LATIN SMALL LETTER T
constexpr auto latin_small_letter_u = "\x75";       // LATIN SMALL LETTER U
constexpr auto latin_small_letter_v = "\x76";       // LATIN SMALL LETTER V
constexpr auto latin_small_letter_w = "\x77";       // LATIN SMALL LETTER W
constexpr auto latin_small_letter_x = "\x78";       // LATIN SMALL LETTER X
constexpr auto latin_small_letter_y = "\x79";       // LATIN SMALL LETTER Y
constexpr auto latin_small_letter_z = "\x7A";       // LATIN SMALL LETTER Z
constexpr auto left_curly_bracket = "\x7B";         // LEFT CURLY BRACKET
constexpr auto vertical_line = "\x7C";              // VERTICAL LINE
constexpr auto right_curly_bracket = "\x7D";        // RIGHT CURLY BRACKET
constexpr auto tilde = "\x7E";                      // TILDE
constexpr auto del = "\x7F";                        // DELETE

__CAITLYN_DEF_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_STRING_DEFS_H_
