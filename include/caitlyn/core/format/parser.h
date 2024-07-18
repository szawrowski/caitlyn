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

#include "caitlyn/core/format/converters.h"
#include "caitlyn/core/format/types.h"

namespace cait {
namespace fmt {

inline bool is_digit(const string_t& str) { return str >= 0x30 && str < 0x3A; }

inline spec_t make_spec(const string_t& spec) {
  if (spec[0] != ":") {
    throw error_t{"Incorrect format specifier"};
  }
  spec_t result;
  size_t i = 1;

  // Parse fill character and alignment
  if (i + 1 < spec.size() &&
      (spec[i + 1] == '<' || spec[i + 1] == '>' || spec[i + 1] == '^')) {
    result.fill = spec[i];
    ++i;
    if (spec[i] == '<') {
      result.align = align_t::left;
    } else if (spec[i] == '>') {
      result.align = align_t::right;
    } else if (spec[i] == '^') {
      result.align = align_t::center;
    }
    ++i;
  } else if (spec[i] == '<') {
    result.align = align_t::left;
    ++i;
  } else if (spec[i] == '>') {
    result.align = align_t::right;
    ++i;
  } else if (spec[i] == '^') {
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
  if (i < spec.size() && spec[i] == '.') {
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
    if (spec[i] == 's') {
      result.type = type_t::string;
    } else if (spec[i] == 'd') {
      result.type = type_t::integral;
    } else if (spec[i] == 'f') {
      result.type = type_t::floating;
    }
  }
  return result;
}

}  // namespace fmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_PARSER_H_
