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

#include "caitlyn/core/char.h"

namespace cait {

inline std::vector<std::string> split(const std::string& text,
                                      const char_t delim) {
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

inline std::string to_uppercase(std::string value) {
  for (char& c : value) {
    c = to_uppercase(c);
  }
  return value;
}

inline std::string to_lowercase(std::string value) {
  for (char& c : value) {
    c = to_lowercase(c);
  }
  return value;
}

inline std::string escape_string(const std::string& str) {
  ostrstream_t oss;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == get_char(ascii_t::rev_solidus) && i + 1 < str.size()) {
      if (str[i + 1] == get_char(ascii_t::quot_mark)) {
        oss << get_char(ascii_t::quot_mark);
        ++i;  // Skip the escaped character
      } else if (str[i + 1] == get_char(ascii_t::quest_mark)) {
        oss << get_char(ascii_t::quest_mark);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::rev_solidus)) {
        oss << get_char(ascii_t::rev_solidus);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::solidus)) {
        oss << get_char(ascii_t::solidus);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_a)) {
        oss << get_char(ascii_t::bell);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_b)) {
        oss << get_char(ascii_t::backspace);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_f)) {
        oss << get_char(ascii_t::form_feed);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_n)) {
        oss << get_char(ascii_t::line_feed);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_r)) {
        oss << get_char(ascii_t::carriage_ret);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_t)) {
        oss << get_char(ascii_t::char_tab);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_v)) {
        oss << get_char(ascii_t::line_tab);
        ++i;
      } else if (str[i + 1] == get_char(ascii_t::latin_small_letter_u)) {
        if (i + 5 < str.size()) {
          auto hex = str.substr(i + 2, 4);
          // Convert the hexadecimal representation to a character
          const char c = static_cast<char>(std::stoi(hex, nullptr, 16));
          oss << c;
          i += 5;  // Skip the escaped sequence
        } else {
          // Incomplete escape sequence, handle it as an error
          oss << get_char(ascii_t::rev_solidus) + str[i + 1];
        }
      } else {
        // Invalid escape sequence, handle it as an error
        oss << get_char(ascii_t::rev_solidus) + str[i + 1];
      }
    } else {
      oss << str[i];
    }
  }
  return oss.str();
}

inline bool_t is_number(const std::string& str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), is_digit);
}

inline size_t find_first_nonws(const std::string& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

inline size_t find_last_nonws(const std::string& str) {
  for (size_t i = str.size() - 1; i > 0; --i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

template <typename T>
const char_t* get_as_string(T value);

template <>
inline const char_t* get_as_string(const bool_t value) {
  return value ? "true" : "false";
}

template <>
inline const char_t* get_as_string(null_t) {
  return "null";
}

}  // namespace cait

#endif  // CAITLYN_CORE_STRING_UTILITY_H_
