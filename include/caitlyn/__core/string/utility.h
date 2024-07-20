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

#ifndef CAITLYN_CORE_STRING_UTILITY_H_
#define CAITLYN_CORE_STRING_UTILITY_H_

#include <algorithm>
#include <sstream>

#include <caitlyn/__core/traits/types/base.h>
#include <caitlyn/__core/traits/types/primary.h>
#include "caitlyn/__core/string/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

inline bool is_space(const basic_string_t<char>& value) {
  return value == def::character_tabulation || value == def::line_feed ||
         value == def::line_tabulation || value == def::form_feed ||
         value == def::carriage_return || value == def::space;
}

inline std::vector<std::string> split(const std::string& text,
                                      const char delim) {
  std::stringstream ss{text};
  std::string item;
  std::vector<std::string> data;

  while (std::getline(ss, item, delim)) {
    data.emplace_back(item);
  }
  return data;
}

inline std::string repeat(const std::string& str, const size_t count) {
  if (count < 2) {
    return str;
  }
  std::stringstream ss;
  for (size_t i = 0; i < count; ++i) {
    ss << str;
  }
  return ss.str();
}

inline basic_string_t<char> escape_string(const basic_string_t<char>& str) {
  std::ostringstream oss;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == def::reverse_solidus && i + 1 < str.size()) {
      if (str[i + 1] == def::quotation_mark) {
        oss << def::quotation_mark;
        ++i;  // Skip the escaped character
      } else if (str[i + 1] == def::question_mark) {
        oss << def::question_mark;
        ++i;
      } else if (str[i + 1] == def::reverse_solidus) {
        oss << def::reverse_solidus;
        ++i;
      } else if (str[i + 1] == def::solidus) {
        oss << def::solidus;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_a) {
        oss << def::bell;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_b) {
        oss << def::backspace;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_f) {
        oss << def::form_feed;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_n) {
        oss << def::line_feed;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_r) {
        oss << def::carriage_return;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_t) {
        oss << def::character_tabulation;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_v) {
        oss << def::line_tabulation;
        ++i;
      } else if (str[i + 1] == def::latin_small_letter_u) {
        if (i + 5 < str.size()) {
          auto hex = str.substr(i + 2, 4).str();
          // Convert the hexadecimal representation to a character
          oss << static_cast<char>(std::stoi(hex, nullptr, 16));
          i += 5;  // Skip the escaped sequence
        } else {
          // Incomplete escape sequence, handle it as an error
          oss << def::reverse_solidus << str[i + 1];
        }
      } else {
        // Invalid escape sequence, handle it as an error
        oss << def::reverse_solidus << str[i + 1];
      }
    } else {
      oss << str[i];
    }
  }
  return oss.str();
}

inline bool is_digit(const basic_string_t<char>& str) {
  return str >= def::digit_zero && str <= def::digit_nine;
}

inline bool is_number(const basic_string_t<char>& str) {
  return str.not_empty() && std::all_of(str.begin(), str.end(), is_digit);
}

inline bool is_uppercase(const basic_string_t<char>& value) {
  return value >= def::latin_capital_letter_a &&
         value <= def::latin_capital_letter_z;
}

inline bool is_lowercase(const basic_string_t<char>& value) {
  return value >= def::latin_small_letter_a &&
         value <= def::latin_small_letter_a;
}

inline bool is_alpha(const basic_string_t<char>& value) {
  return is_uppercase(value) || is_lowercase(value);
}

inline basic_string_t<char> to_uppercase(const basic_string_t<char>& value) {
  basic_string_t<char> result = value;
  for (size_t i = 0; i < result.length(); ++i) {
    if (result[i] >= def::latin_small_letter_a &&
        result[i] <= def::latin_small_letter_z) {
      const auto tmp = result.get_chars_at(i)[0];
      result[i] = static_cast<char>(tmp - (def::latin_small_letter_a[0] -
                                           def::latin_capital_letter_a[0]));
    }
  }
  return result;
}

inline basic_string_t<char> to_lowercase(const basic_string_t<char>& value) {
  basic_string_t<char> result = value;
  for (size_t i = 0; i < result.length(); ++i) {
    if (result[i] >= def::latin_capital_letter_a &&
        result[i] <= def::latin_capital_letter_z) {
      const auto tmp = result.get_chars_at(i)[0];
      result[i] = static_cast<char>(tmp + (def::latin_small_letter_a[0] -
                                           def::latin_capital_letter_a[0]));
    }
  }
  return result;
}

inline size_t find_first_nonws(const basic_string_t<char>& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

inline size_t find_last_nonws(const basic_string_t<char>& str) {
  for (size_t i = str.size() - 1; i > 0; --i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

// inline int char_to_digit(const char value) {
//   if (value >= 0x30 && value <= 0x39) {
//     return value - 0x30;
//   }
//   return -1;
// }
//
// inline int char_to_int(const char value) {
//   return std::isdigit(value) ? value - 0x30 : std::tolower(value - 0x61) +
//   0xA;
// }

template <typename T>
required_t<is_boolean<T>(), const char*> to_string(T value) {
  return value ? "true" : "false";
}

template <typename T>
required_t<is_null_ptr<T>(), const char*> to_string(T) {
  return "null";
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_STRING_UTILITY_H_
