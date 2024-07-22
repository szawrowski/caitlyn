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

#include "caitlyn/__core/format/error.h"
#include "caitlyn/__core/format/specifier.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_FORMAT_NAMESPACE_BEGIN

inline void parse_view(const basic_string_t<char>& config, spec_t& spec,
                       size_t& pos) {
  if (pos + 1 < config.size() && config[pos] == def::number_sign) {
    if (config[pos + 1] == def::latin_small_letter_b) {
      spec.repr = repr_t::binary_pref;
      pos += 2;
    } else if (config[pos + 1] == def::latin_small_letter_o) {
      spec.repr = repr_t::octal_pref;
      pos += 2;
    } else if (config[pos + 1] == def::latin_small_letter_x) {
      spec.repr = repr_t::hex_pref;
      pos += 2;
    }
  } else if (config[pos] == def::latin_small_letter_b) {
    spec.repr = repr_t::binary;
    ++pos;
  } else if (config[pos] == def::latin_capital_letter_o) {
    spec.repr = repr_t::octal;
    ++pos;
  } else if (config[pos] == def::latin_capital_letter_x) {
    spec.repr = repr_t::hex;
    ++pos;
  }
}

inline void set_fill(const basic_string_t<char>& config, spec_t& spec,
                     size_t& pos) {
  spec.fill = config[pos++];
}

// Parse fill character and alignment
inline void parse_alignment(const basic_string_t<char>& config, spec_t& spec,
                            size_t& pos) {
  if (pos + 1 < config.size() && (config[pos + 1] == def::less_than_sign ||
                                  config[pos + 1] == def::greater_than_sign ||
                                  config[pos + 1] == def::circumflex_accent)) {
    set_fill(config, spec, pos);

    if (config[pos] == def::less_than_sign) {
      spec.align = align_t::left;
      ++pos;
    } else if (config[pos] == def::greater_than_sign) {
      spec.align = align_t::right;
      ++pos;
    } else if (config[pos] == def::circumflex_accent) {
      spec.align = align_t::center;
      ++pos;
    }
  } else if (config[pos] == def::less_than_sign) {
    spec.align = align_t::left;
    ++pos;
  } else if (config[pos] == def::greater_than_sign) {
    spec.align = align_t::right;
    ++pos;
  } else if (config[pos] == def::circumflex_accent) {
    spec.align = align_t::center;
    ++pos;
  }
}

inline void parse_width(const basic_string_t<char>& config, spec_t& spec,
                        size_t& pos) {
  if (pos < config.size() && is_digit(config[pos].get_codepoint())) {
    spec.width = std::stoul(config.substr(pos).str());
    while (pos < config.size() && is_digit(config[pos].get_codepoint())) {
      ++pos;
    }
  }
}

inline void parse_precision(const basic_string_t<char>& config, spec_t& spec,
                            size_t& pos) {
  if (pos < config.size() && config[pos] == def::full_stop) {
    ++pos;
    if (pos < config.size() && is_digit(config[pos].get_codepoint())) {
      spec.precision = std::stoi(config.substr(pos).str());
      while (pos < config.size() && is_digit(config[pos].get_codepoint())) {
        ++pos;
      }
    }
  }
}

inline void parse_type(const basic_string_t<char>& config, spec_t& spec,
                       size_t& pos) {
  if (pos < config.size()) {
    if (config[pos] == def::latin_small_letter_s) {
      spec.type = value_t::string;
      ++pos;
    } else if (config[pos] == def::latin_small_letter_d) {
      spec.type = value_t::integral;
      ++pos;
    } else if (config[pos] == def::latin_small_letter_f) {
      spec.type = value_t::floating;
      ++pos;
    }
  }
}

inline spec_t make_spec(const basic_string_t<char>& config) {
  spec_t spec;
  size_t pos = 0;

  if (config[pos++] != def::colon) {
    throw error_t{"Incorrect format specifier"};
  }
  parse_view(config, spec, pos);
  parse_alignment(config, spec, pos);
  parse_width(config, spec, pos);
  parse_precision(config, spec, pos);
  parse_type(config, spec, pos);

  return spec;
}

__CAITLYN_FORMAT_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_PARSER_H_
