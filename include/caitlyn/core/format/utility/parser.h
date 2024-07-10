// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_FORMAT_PARSER_H_
#define CAITLYN_CORE_STRING_FORMAT_PARSER_H_

#include "caitlyn/core/format/utility/converters.h"

namespace cait {
namespace strfmt {
namespace __detail {

static format_spec_t parse_format_spec(const std::string& spec) {
  format_spec_t result;
  size_t i{};

  // Parse alignment
  if (i < spec.size() && (spec[i] == get_char(ascii_t::less_than_sign) ||
                          spec[i] == get_char(ascii_t::greater_than_sign) ||
                          spec[i] == get_char(ascii_t::circumflex_accent))) {
    result.align = spec[i] == get_char(ascii_t::less_than_sign)
                       ? format_align_t::left
                   : spec[i] == get_char(ascii_t::greater_than_sign)
                       ? format_align_t::right
                       : format_align_t::center;
    ++i;
                          }

  // Parse fill character
  if (i < spec.size() && is_digit(spec[i])) {
    result.fill = spec[i];
    ++i;
  }

  // Parse width
  if (i < spec.size() && is_digit(spec[i])) {
    result.width = std::stoi(spec.substr(i));
    while (i < spec.size() && is_digit(spec[i])) ++i;
  }

  // Parse precision
  if (i < spec.size() && spec[i] == '.') {
    ++i;
    if (i < spec.size() && is_digit(spec[i])) {
      result.precision = std::stoi(spec.substr(i));
      while (i < spec.size() && is_digit(spec[i])) ++i;
    }
  }

  // Parse type
  if (i < spec.size() && (spec[i] == get_char(ascii_t::latin_small_letter_s) ||
                          spec[i] == get_char(ascii_t::latin_small_letter_d) ||
                          spec[i] == get_char(ascii_t::latin_small_letter_f))) {
    result.type = spec[i] == get_char(ascii_t::latin_small_letter_s)
                      ? format_type_t::string
                  : spec[i] == get_char(ascii_t::latin_small_letter_d)
                      ? format_type_t::integral
                      : format_type_t::floating_point;
                          }

  return result;
}

}  // namespace __detail
}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_STRING_FORMAT_PARSER_H_
