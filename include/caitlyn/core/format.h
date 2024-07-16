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
  const auto origin = str.std_string();
  std::ostringstream result;

  const std::vector<std::string> arguments = {
      strfmt::__detail::to_string(std::forward<Args>(args), {})...};
  size_t arg_index{};
  size_t pos{};

  while (pos < origin.size()) {
    if (origin[pos] == get_char(ascii_t::left_curly_br)) {
      if (pos + 1 < origin.size() &&
          origin[pos + 1] == get_char(ascii_t::left_curly_br)) {
        result << get_char(ascii_t::left_curly_br);
        pos += 2;
      } else {
        const size_t end = origin.find(get_char(ascii_t::right_curly_br), pos);
        if (end == std::string::npos) {
          throw strfmt::error_t{"Mismatched braces in format string"};
        }
        std::string spec = origin.substr(pos + 1, end - pos - 1);
        if (arg_index >= arguments.size()) {
          throw strfmt::error_t{"Argument index out of range"};
        }
        result << strfmt::__detail::to_string(
            arguments[arg_index++], strfmt::__detail::parse_format_spec(spec));
        pos = end + 1;
      }
    } else if (origin[pos] == get_char(ascii_t::right_curly_br)) {
      if (pos + 1 < origin.size() &&
          origin[pos + 1] == get_char(ascii_t::right_curly_br)) {
        result << get_char(ascii_t::right_curly_br);
        pos += 2;
      } else {
        throw strfmt::error_t{"Single '}' in format string"};
      }
    } else {
      result << origin[pos++];
    }
  }
  return result.str();
}

}  // namespace cait

#if __caitlyn_has_cxx20
  #include <format>
#endif

#endif  // CAITLYN_CORE_FORMAT_H_
