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

#ifndef CAITLYN_CORE_STRING_FORMAT_FORMAT_H_
#define CAITLYN_CORE_STRING_FORMAT_FORMAT_H_

#include <vector>

#include "caitlyn/core/format/utility/utility.h"

namespace cait {

template <typename... Args>
static std::string fmt(const std::string& str, Args&&... args) {
  std::ostringstream result;
  const std::vector<std::string> arguments = {
      strfmt::__detail::to_string(std::forward<Args>(args), {})...};
  size_t arg_index{};
  size_t pos{};

  while (pos < str.size()) {
    if (str[pos] == get_char(ascii_t::left_curly_br)) {
      if (pos + 1 < str.size() &&
          str[pos + 1] == get_char(ascii_t::left_curly_br)) {
        result << get_char(ascii_t::left_curly_br);
        pos += 2;
      } else {
        const size_t end = str.find(get_char(ascii_t::right_curly_br), pos);
        if (end == std::string::npos) {
          throw strfmt::format_error_t{"Mismatched braces in format string"};
        }
        std::string spec = str.substr(pos + 1, end - pos - 1);
        if (arg_index >= arguments.size()) {
          throw strfmt::format_error_t{"Argument index out of range"};
        }
        result << strfmt::__detail::to_string(
            arguments[arg_index++], strfmt::__detail::parse_format_spec(spec));
        pos = end + 1;
      }
    } else if (str[pos] == get_char(ascii_t::right_curly_br)) {
      if (pos + 1 < str.size() &&
          str[pos + 1] == get_char(ascii_t::right_curly_br)) {
        result << get_char(ascii_t::right_curly_br);
        pos += 2;
      } else {
        throw strfmt::format_error_t{"Single '}' in format string"};
      }
    } else {
      result << str[pos++];
    }
  }
  return result.str();
}

}  // namespace cait

#endif  // CAITLYN_CORE_STRING_FORMAT_FORMAT_H_
