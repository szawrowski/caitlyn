// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_FORMAT_FORMAT_H_
#define CAITLYN_CORE_STRING_FORMAT_FORMAT_H_

#include "caitlyn/core/format/utility/utility.h"

namespace cait {

template <typename... Args>
static std::string format(const std::string& str, Args&&... args) {
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
