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

#include "caitlyn/core/format/utility/converters.h"

namespace cait {
namespace strfmt {

inline bool is_digit(const string_t& str) {
  return str >= 0x30 && str < 0x3A;
}

inline spec_t parse_format_spec(const string_t& spec) {
  spec_t result;
  size_t i{};

  if (i >= spec.size()) {
    return result;
  }

  // Parse alignment
  if (spec[i] == "<") {
    result.align = align_t::left;
    ++i;
  } else if (spec[i] == ">") {
    result.align = align_t::right;
    ++i;
  } else if (spec[i] == "^") {
    result.align = align_t::center;
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
  if (i < spec.size() && spec[i] == ".") {
    ++i;
    if (i < spec.size() && is_digit(spec[i])) {
      result.precision = std::stoi(spec.substr(i).c_str());
      while (i < spec.size() && is_digit(spec[i])) ++i;
    }
  }

  // Parse type
  if (i < spec.size()) {
    if (spec[i] == "s") {
      result.type = type_t::string;
    } else if (spec[i] == "d") {
      result.type = type_t::integral;
    } else if (spec[i] == "f") {
      result.type = type_t::floating_point;
    }
  }
  return result;
}

}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_UTILITY_PARSER_H_
