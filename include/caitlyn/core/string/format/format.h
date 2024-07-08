// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_FORMAT_FORMAT_H_
#define CAITLYN_CORE_STRING_FORMAT_FORMAT_H_

#include "caitlyn/core/char/utility/char_utility.h"
#include <caitlyn/core/unicode/types/unicode_string.h>
#include "caitlyn/core/string/format/defs/format_definitions.h"

__caitlyn_begin_global_namespace
__caitlyn_begin_format_namespace

enum class align_t { left, right, center };

enum class type_t { string, integral, floating_point };

struct format_spec_t {
  align_t align = align_t::left;
  int_t width = 0;
  char_t fill = ' ';
  type_t type = type_t::string;
  int_t precision = -1;
};

class format_error_t final : public std::runtime_error {
public:
  explicit format_error_t(const string_t& message)
      : std::runtime_error(message) {}
};

__caitlyn_begin_detail_namespace

template <typename T>
static typename std::enable_if<std::is_integral<T>::value, string_t>::type
to_string(const T& value, const format_spec_t& spec) {
  ostrstream_t oss;
  oss << std::fixed << std::setprecision(0);

  if (spec.type == type_t::integral) {
    oss << static_cast<int64_t>(value);
  } else {
    oss << value;
  }
  string_t str = oss.str();

  if (static_cast<int>(str.size()) < spec.width) {
    switch (spec.align) {
      case align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

template <typename T>
static typename std::enable_if<std::is_floating_point<T>::value, string_t>::type
to_string(const T& value, const format_spec_t& spec) {
  ostrstream_t oss;
  oss << std::fixed
      << std::setprecision(spec.precision >= 0 ? spec.precision : 6);

  oss << (spec.type == type_t::floating_point ? static_cast<float64_t>(value)
                                              : value);

  string_t str = oss.str();
  if (static_cast<ssize_t>(str.size()) < spec.width) {
    switch (spec.align) {
      case align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

static string_t to_string(const string_t& value, const format_spec_t& spec) {
  string_t str = value;
  if (static_cast<int_t>(str.size()) < spec.width) {
    switch (spec.align) {
      case align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

static string_t to_string(const char_t* value, const format_spec_t& spec) {
  return to_string(string_t{value}, spec);
}

template <typename T>
static typename std::enable_if<std::is_same<T, unistr_t>::value, string_t>::type
to_string(const T& value, const format_spec_t& spec) {
  return to_string(value.to_std_string(), spec);
}

template <typename T>
static
    typename std::enable_if<std::is_same<T, unichar_t>::value, string_t>::type
    to_string(const T& value, const format_spec_t& spec) {
  return to_string(char_to_std_string<u8char_t>(value.get_code_point()), spec);
}

static format_spec_t parse_format_spec(const string_t& spec) {
  format_spec_t result;
  size_t i{};

  // Parse alignment
  if (i < spec.size() && (spec[i] == get_symbol(char_hex_t::less_than) ||
                          spec[i] == get_symbol(char_hex_t::greater_then) ||
                          spec[i] == get_symbol(char_hex_t::caret))) {
    result.align = spec[i] == get_symbol(char_hex_t::less_than) ? align_t::left
                   : spec[i] == get_symbol(char_hex_t::greater_then)
                       ? align_t::right
                       : align_t::center;
    ++i;
  }

  // Parse fill character
  if (i < spec.size() && is_digit(spec[i])) {
    result.fill = spec[i];
    ++i;
  }

  // Parse width
  if (i < spec.size() && is_digit(spec[i])) {
    result.width = std::stoi(spec.substr(i));
    while (i < spec.size() && is_digit(spec[i])) ++i;
  }

  // Parse precision
  if (i < spec.size() && spec[i] == '.') {
    ++i;
    if (i < spec.size() && is_digit(spec[i])) {
      result.precision = std::stoi(spec.substr(i));
      while (i < spec.size() && is_digit(spec[i])) ++i;
    }
  }

  // Parse type
  if (i < spec.size() && (spec[i] == get_symbol(char_hex_t::lowercase_s) ||
                          spec[i] == get_symbol(char_hex_t::lowercase_d) ||
                          spec[i] == get_symbol(char_hex_t::lowercase_f))) {
    result.type = spec[i] == get_symbol(char_hex_t::lowercase_s)
                      ? type_t::string
                  : spec[i] == get_symbol(char_hex_t::lowercase_d)
                      ? type_t::integral
                      : type_t::floating_point;
  }

  return result;
}

__caitlyn_end_detail_namespace
__caitlyn_end_format_namespace

template <typename... Args>
static string_t fmt(const string_t& str, Args&&... args) {
  ostrstream_t result;
  const std::vector<string_t> arguments = {
      format::__detail::to_string(std::forward<Args>(args), {})...};
  size_t arg_index{};
  size_t pos{};

  while (pos < str.size()) {
    if (str[pos] == get_symbol(char_hex_t::opening_curly_bracket)) {
      if (pos + 1 < str.size() &&
          str[pos + 1] == get_symbol(char_hex_t::opening_curly_bracket)) {
        result << get_symbol(char_hex_t::opening_curly_bracket);
        pos += 2;
      } else {
        const size_t end =
            str.find(get_symbol(char_hex_t::closing_curly_bracket), pos);
        if (end == string_t::npos) {
          throw format::format_error_t{"Mismatched braces in format string"};
        }
        string_t spec = str.substr(pos + 1, end - pos - 1);
        if (arg_index >= arguments.size()) {
          throw format::format_error_t{"Argument index out of range"};
        }
        result << format::__detail::to_string(
            arguments[arg_index++], format::__detail::parse_format_spec(spec));
        pos = end + 1;
      }
    } else if (str[pos] == get_symbol(char_hex_t::closing_curly_bracket)) {
      if (pos + 1 < str.size() &&
          str[pos + 1] == get_symbol(char_hex_t::closing_curly_bracket)) {
        result << get_symbol(char_hex_t::closing_curly_bracket);
        pos += 2;
      } else {
        throw format::format_error_t{"Single '}' in format string"};
      }
    } else {
      result << str[pos++];
    }
  }
  return result.str();
}

template <typename... Args>
static void print(const string_t& str, Args&&... args) {
  std::cout << fmt(str, std::forward<Args>(args)...);
}

template <typename... Args>
static void println(const string_t& str, Args&&... args) {
  std::cout << fmt(str, std::forward<Args>(args)...) << std::endl;
}

template <typename... Args>
static void eprint(const string_t& str, Args&&... args) {
  std::cerr << fmt(str, std::forward<Args>(args)...);
}

template <typename... Args>
static void eprintln(const string_t& str, Args&&... args) {
  std::cerr << fmt(str, std::forward<Args>(args)...) << std::endl;
}

template <typename... Args>
static void log(const string_t& str, Args&&... args) {
  std::clog << fmt(str, std::forward<Args>(args)...) << std::endl;
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_STRING_FORMAT_FORMAT_H_
