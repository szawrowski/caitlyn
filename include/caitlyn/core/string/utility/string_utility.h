// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_
#define CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_

#include "caitlyn/core/char/char.h"
#include "caitlyn/core/containers.h"
#include "caitlyn/core/string/defs/string_definitions.h"

BEGIN_CAITLYN_NS

static vector_t<string_t> split(const string_t& text, const char_t delim) {
  strstream_t ss{text};
  string_t item;
  vector_t<string_t> data;

  while (std::getline(ss, item, delim)) {
    data.emplace_back(item);
  }
  return data;
}

static string_t repeat(const string_t& str, const size_t count) {
  if (count < 2) {
    return str;
  }
  strstream_t ss;
  for (size_t i = 0; i < count; ++i) {
    ss << str;
  }
  return ss.str();
}

static string_t to_uppercase(string_t value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](const char_t c) { return to_uppercase(c); });
  return value;
}

static string_t to_lowercase(string_t value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](const char_t c) { return to_lowercase(c); });
  return value;
}

static string_t escape_string(const string_t& str) {
  ostrstream_t oss;

  for (size_t i = 0; i < str.size(); ++i) {
    if (str[i] == get_symbol(char_hex_t::backslash) && i + 1 < str.size()) {
      switch (str[i + 1]) {
        case get_symbol(char_hex_t::double_quote):
          oss << get_symbol(char_hex_t::double_quote);
          break;
        case get_symbol(char_hex_t::question_mark):
          oss << get_symbol(char_hex_t::question_mark);
          break;
        case get_symbol(char_hex_t::backslash):
          oss << get_symbol(char_hex_t::backslash);
          break;
        case get_symbol(char_hex_t::slash):
          oss << get_symbol(char_hex_t::slash);
          break;
        case get_symbol(char_hex_t::lowercase_a):
          oss << get_symbol(char_hex_t::audible_bell);
          break;
        case get_symbol(char_hex_t::lowercase_b):
          oss << get_symbol(char_hex_t::backspace);
          break;
        case get_symbol(char_hex_t::lowercase_f):
          oss << get_symbol(char_hex_t::form_feed);
          break;
        case get_symbol(char_hex_t::lowercase_n):
          oss << get_symbol(char_hex_t::line_feed);
          break;
        case get_symbol(char_hex_t::lowercase_r):
          oss << get_symbol(char_hex_t::carriage_return);
          break;
        case get_symbol(char_hex_t::lowercase_t):
          oss << get_symbol(char_hex_t::horizontal_tab);
          break;
        case get_symbol(char_hex_t::lowercase_v):
          oss << get_symbol(char_hex_t::vertical_tab);
          break;
        case get_symbol(char_hex_t::lowercase_u): {
          if (i + 5 < str.size()) {
            auto hex = str.substr(i + 2, 4);
            // Convert the hexadecimal representation to a character
            const char c = static_cast<char>(std::stoi(hex, nullptr, 16));
            oss << c;
            i += 5;  // Skip the escaped sequence
          } else {
            // Incomplete escape sequence, handle it as an error
            oss << get_symbol(char_hex_t::backslash) + str[i + 1];
          }
          break;
        }
        default:
          // Invalid escape sequence, handle it as an error
          oss << get_symbol(char_hex_t::backslash) + str[i + 1];
          break;
      }
      ++i;  // Skip the escaped character
    } else {
      oss << str[i];
    }
  }
  return oss.str();
}

static bool_t is_number(const string_t& str) {
  return !str.empty() &&
         std::find_if(str.begin(), str.end(), [](const unsigned char c) {
           return !std::isdigit(c);
         }) == str.end();
}

static size_t find_first_nonws(const string_t& str) {
  for (size_t i = 0; i < str.size(); ++i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

static size_t find_last_nonws(const string_t& str) {
  for (size_t i = str.size() - 1; i > 0; --i) {
    if (!is_space(str[i])) {
      return i;
    }
  }
  return str.size();
}

template <typename T>
static auto get_as_string(T value);

template <>
inline auto get_as_string(const bool_t value) {
  return value ? "true" : "false";
}

template <>
inline auto get_as_string(null_t) {
  return "null";
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_
