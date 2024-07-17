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

#ifndef CAITLYN_CORE_FORMAT_UTILITY_PARSER_H_
#define CAITLYN_CORE_FORMAT_UTILITY_PARSER_H_

#include "caitlyn/core/char.h"
#include "caitlyn/core/format/utility/converters.h"

namespace cait {
namespace strfmt {
namespace __detail {

inline bool is_digit(const string_t& str) {
  return str >= 0x30 && str < 0x3A;
}

inline spec_t parse_format_spec(const string_t& spec) {
  spec_t result;
  size_t i{};

  // Parse alignment
  if (i < spec.size() && (spec[i] == get_char(ascii_t::less_than_sign) ||
                          spec[i] == get_char(ascii_t::greater_than_sign) ||
                          spec[i] == get_char(ascii_t::circumflex_accent))) {
    result.align = spec[i] == get_char(ascii_t::less_than_sign) ? align_t::left
                   : spec[i] == get_char(ascii_t::greater_than_sign)
                       ? align_t::right
                       : align_t::center;
    ++i;
  }

  // Parse fill character
  if (i < spec.size() && is_digit(spec[i])) {
    result.fill = spec[i];
    ++i;
  }

  // Parse width
  if (i < spec.size() && is_digit(spec[i])) {
    result.width = std::stoi(spec.substr(i).c_str());
    while (i < spec.size() && is_digit(spec[i])) {
      ++i;
    }
  }

  // Parse precision
  if (i < spec.size() && spec[i] == '.') {
    ++i;
    if (i < spec.size() && is_digit(spec[i])) {
      result.precision = std::stoi(spec.substr(i).c_str());
      while (i < spec.size() && is_digit(spec[i])) ++i;
    }
  }

  // Parse type
  if (i < spec.size() && (spec[i] == get_char(ascii_t::latin_small_letter_s) ||
                          spec[i] == get_char(ascii_t::latin_small_letter_d) ||
                          spec[i] == get_char(ascii_t::latin_small_letter_f))) {
    result.type = spec[i] == get_char(ascii_t::latin_small_letter_s)
                      ? type_t::string
                  : spec[i] == get_char(ascii_t::latin_small_letter_d)
                      ? type_t::integral
                      : type_t::floating_point;
  }

  return result;
}

}  // namespace __detail
}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_UTILITY_PARSER_H_
