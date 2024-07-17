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

#ifndef CAITLYN_CORE_FORMAT_H_
#define CAITLYN_CORE_FORMAT_H_

#include <vector>

#include "caitlyn/core/format/utility.h"

namespace cait {

template <typename... Args>
string_t format(const string_t& str, Args&&... args) {
  std::ostringstream result;

  const std::vector<string_t> arguments = {
    strfmt::to_string(std::forward<Args>(args), {})...};

  size_t pos = 0;

  while (pos < str.size()) {
    if (str[pos] == "{") {
      if (pos + 1 < str.size() && str[pos + 1] == "{") {
        result << "{";
        pos += 2;
      } else {
        const size_t end = str.find("}", pos);
        if (end == string_t::npos) {
          throw strfmt::error_t{"Mismatched braces in format string"};
        }
        const auto spec = str.substr(pos + 1, end - pos - 1);
        size_t arg_index = 0;
        size_t spec_pos = 0;

        // Parse the index if it exists
        if (!spec.is_empty() && strfmt::is_digit(spec[spec_pos])) {
          size_t index_end = spec_pos;
          while (index_end < spec.size() && strfmt::is_digit(spec[index_end])) {
            ++index_end;
          }
          try {
            arg_index = std::stoul(spec.substr(spec_pos, index_end - spec_pos).str());
          } catch (const std::out_of_range&) {
            throw strfmt::error_t{"Argument index out of range"};
          }
          spec_pos = index_end;
          if (spec_pos < spec.size() && spec[spec_pos] == ":") {
            ++spec_pos;
          }
        }

        if (arg_index >= arguments.size()) {
          throw strfmt::error_t{"Argument index out of range"};
        }

        const auto format_spec = spec.substr(spec_pos);
        result << strfmt::to_string(
            arguments[arg_index], strfmt::parse_format_spec(format_spec));
        pos = end + 1;
      }
    } else if (str[pos] == "}") {
      if (pos + 1 < str.size() && str[pos + 1] == "}") {
        result << "}";
        pos += 2;
      } else {
        throw strfmt::error_t{"Single '}' in format string"};
      }
    } else {
      result << str[pos++];
    }
  }
  return result.str();
}

}  // namespace cait

#if __caitlyn_has_cxx20
  #include <format>
#endif

#endif  // CAITLYN_CORE_FORMAT_H_
