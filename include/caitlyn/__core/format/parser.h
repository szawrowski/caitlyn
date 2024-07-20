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

#ifndef CAITLYN_CORE_FORMAT_PARSER_H_
#define CAITLYN_CORE_FORMAT_PARSER_H_

#include "caitlyn/__core/format/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_FORMAT_NAMESPACE_BEGIN

inline specifier make_spec(const basic_string_t<char>& spec) {
  if (spec[0] != def::colon) {
    throw error_t{"Incorrect format specifier"};
  }
  specifier result;
  size_t i = 1;

  // Parse fill character and alignment
  if (i + 1 < spec.size() && (spec[i + 1] == def::less_than_sign ||
                              spec[i + 1] == def::greater_than_sign ||
                              spec[i + 1] == def::circumflex_accent)) {
    result.fill = spec[i];
    ++i;
    if (spec[i] == def::less_than_sign) {
      result.align = align_t::left;
    } else if (spec[i] == def::greater_than_sign) {
      result.align = align_t::right;
    } else if (spec[i] == def::circumflex_accent) {
      result.align = align_t::center;
    }
    ++i;
  } else if (spec[i] == def::less_than_sign) {
    result.align = align_t::left;
    ++i;
  } else if (spec[i] == def::greater_than_sign) {
    result.align = align_t::right;
    ++i;
  } else if (spec[i] == def::circumflex_accent) {
    result.align = align_t::center;
    ++i;
  }

  // Parse width
  if (i < spec.size() && is_digit(spec[i])) {
    result.width = std::stoul(spec.substr(i).str());
    while (i < spec.size() && is_digit(spec[i])) {
      ++i;
    }
  }

  // Parse precision
  if (i < spec.size() && spec[i] == def::full_stop) {
    ++i;
    if (i < spec.size() && is_digit(spec[i])) {
      result.precision = std::stoi(spec.substr(i).str());
      while (i < spec.size() && is_digit(spec[i])) {
        ++i;
      }
    }
  }

  // Parse type
  if (i < spec.size()) {
    if (spec[i] == def::latin_small_letter_s) {
      result.type = value_t::string;
    } else if (spec[i] == def::latin_small_letter_d) {
      result.type = value_t::integer;
    } else if (spec[i] == def::latin_small_letter_f) {
      result.type = value_t::floating;
    }
  }
  return result;
}

__CAITLYN_FORMAT_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_PARSER_H_
