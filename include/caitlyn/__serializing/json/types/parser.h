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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_

#include "caitlyn/__core/string.h"
#include "caitlyn/__serializing/json/types/data.h"
#include "caitlyn/__serializing/json/types/error.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

class parser_t {
public:
  using string_type = basic_string_t<char>;
  using size_type = size_t;

public:
  static parser_t parse(const string_type& json) {
    parser_t parser{json};

    if (json.is_empty()) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(0);
      return parser;
    }
    const auto first = find_first_nonws(json);
    const auto last = find_last_nonws(json);

    if (json[first] != def::left_curly_bracket) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(first);
      return parser;
    }
    if (json[last] != def::right_curly_bracket) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(last);
      return parser;
    }
    parser.data_ = parser.parse_value();
    return parser;
  }

  bool has_error() const { return error_ != error_t::no_error; }

  error_t get_error() const { return error_; }

  data_t get_data() const { return data_; }

private:
  parser_t(const string_type& json)
      : error_{error_t::no_error}, json_{json}, position_{} {}

  data_t parse_value() {
    skip_ws();

    if (position_ >= json_.size()) {
      return data_t{};
    }
    const auto current_char = json_[position_];

    if (current_char == def::quotation_mark) {
      return parse_string();
    }
    if (current_char == def::left_curly_bracket) {
      return parse_object();
    }
    if (current_char == def::left_square_bracket) {
      return parse_array();
    }
    if (current_char == def::latin_small_letter_t ||
        current_char == def::latin_small_letter_f) {
      return parse_boolean();
    }
    if (current_char == def::latin_small_letter_n) {
      return parse_null();
    }
    if (is_digit(current_char) || current_char == def::hyphen_minus ||
        current_char == def::plus_sign) {
      return parse_number();
    }
    set_error(error_t::unexpected_character);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_object() {
    data_t result = make_object();
    next();
    skip_ws();

    while (position_ < json_.size()) {
      skip_ws();

      if (json_[position_] == def::right_curly_bracket) {
        next();
        return result;
      }
      if (json_[position_] == def::quotation_mark) {
        next();
        const auto key_end = json_.find(def::quotation_mark, position_);

        if (key_end == string_type::npos) {
          set_error(error_t::unterminated_string);
          set_error_position(position_);
          return data_t{};
        }
        string_type key = json_.substr(position_, key_end - position_);
        position_ = key_end + 1;

        skip_ws();
        if (json_[position_] != def::colon) {
          set_error(error_t::missing_colon);
          set_error_position(position_);
          return data_t{};
        }
        next();
        skip_ws();
        result[key] = parse_value();

        skip_ws();
        if (json_[position_] == def::comma) {
          next();
          skip_ws();

          if (json_[position_] == def::right_curly_bracket) {
            set_error(error_t::trailing_comma);
            set_error_position(position_);
            return data_t{};
          }
        } else if (json_[position_] == def::right_curly_bracket) {
          next();
          return result;
        } else {
          set_error(error_t::unexpected_character);
          set_error_position(position_);
          return data_t{};
        }
      } else {
        set_error(error_t::unexpected_character);
        set_error_position(position_);
        return data_t{};
      }
    }
    set_error(error_t::unterminated_object);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_array() {
    data_t result = make_array();
    next();
    skip_ws();

    while (position_ < json_.size()) {
      skip_ws();

      if (json_[position_] == def::right_square_bracket) {
        next();
        return result;
      }
      const data_t value = parse_value();
      result.append(value);

      skip_ws();
      if (json_[position_] == def::comma) {
        next();
        skip_ws();

        if (json_[position_] == def::right_square_bracket) {
          set_error(error_t::trailing_comma);
          set_error_position(position_);
          return data_t{};
        }
      } else if (json_[position_] == def::right_square_bracket) {
        next();
        return result;
      } else {
        set_error(error_t::unexpected_character);
        error_position_ = position_;
        return data_t{};
      }
    }
    set_error(error_t::unterminated_array);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_null() {
    if (json_.str().compare(position_, 4, to_string(nullptr)) == 0) {
      next(4);
      return make_null();
    }
    set_error(error_t::invalid_value);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_string() {
    next();
    std::ostringstream escaped_stream;

    while (position_ < json_.size() &&
           json_[position_] != def::quotation_mark) {
      if (json_[position_] == def::reverse_solidus) {
        next();
        if (position_ >= json_.size()) {
          set_error(error_t::unterminated_string);
          set_error_position(position_);
          return data_t{};
        }
        if (json_[position_] == def::quotation_mark) {
          escaped_stream << def::quotation_mark;
        } else if (json_[position_] == def::reverse_solidus) {
          escaped_stream << def::reverse_solidus;
        } else if (json_[position_] == def::latin_small_letter_b) {
          escaped_stream << def::backspace;
        } else if (json_[position_] == def::latin_small_letter_f) {
          escaped_stream << def::form_feed;
        } else if (json_[position_] == def::latin_small_letter_n) {
          escaped_stream << def::line_feed;
        } else if (json_[position_] == def::latin_small_letter_r) {
          escaped_stream << def::carriage_return;
        } else if (json_[position_] == def::latin_small_letter_t) {
          escaped_stream << def::character_tabulation;
        } else if (json_[position_] == def::latin_small_letter_u) {
          if (position_ + 4 >= json_.size()) {
            set_error(error_t::invalid_escape_sequence);
            set_error_position(position_);
            return data_t{};
          }
          string_type hex_code = json_.substr(position_ + 1, 4);
          try {
            const uint32_t code_point = std::stoul(hex_code.str(), nullptr, 16);
            escaped_stream << static_cast<char>(code_point);
          } catch (const std::exception&) {
            set_error(error_t::invalid_escape_sequence);
            set_error_position(position_);
            return data_t{};
          }
          position_ += 4;
        } else {
          set_error(error_t::invalid_escape_sequence);
          set_error_position(position_);
          return data_t{};
        }
        next();
      } else {
        escaped_stream << json_[position_];
      }
      next();
    }
    if (json_[position_] == def::quotation_mark) {
      next();
      return escaped_stream.str();
    }
    set_error(error_t::unterminated_string);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_boolean() {
    if (json_.str().compare(position_, 4, to_string(true)) == 0) {
      next(4);
      return true;
    }
    if (json_.str().compare(position_, 5, to_string(false)) == 0) {
      next(5);
      return false;
    }
    set_error(error_t::invalid_value);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_number() {
    data_t result;
    auto end_number = position_;
    while (end_number < json_.size() &&
           (is_digit(json_[end_number]) ||
            json_[end_number] == def::full_stop ||
            json_[end_number] == def::latin_small_letter_e ||
            json_[end_number] == def::latin_capital_letter_e ||
            json_[end_number] == def::hyphen_minus ||
            json_[end_number] == def::plus_sign)) {
      ++end_number;
    }
    const string_type number_str =
        json_.substr(position_, end_number - position_);
    try {
      if (number_str.find(def::plus_sign) != string_type::npos ||
          number_str.find(def::latin_small_letter_e) != string_type::npos ||
          number_str.find(def::latin_capital_letter_e) != string_type::npos) {
        result = std::stod(number_str.str());
      } else {
        result = std::stoll(number_str.str());
      }
    } catch (const std::out_of_range&) {
      set_error(error_t::out_of_range_error);
      set_error_position(position_);
      return data_t{};
    } catch (const std::exception&) {
      set_error(error_t::invalid_number);
      set_error_position(position_);
      return data_t{};
    }
    position_ = end_number;
    return result;
  }

  void skip_ws() {
    while (position_ < json_.size() && is_space(json_[position_])) {
      next();
    }
  }

  void next(const size_type count = 1) { position_ += count; }
  void set_error(const error_t error) { error_ = error; }

  void set_error_position(const size_type position) {
    error_position_ = position;
  }

private:
  data_t data_;
  error_t error_;
  const string_type& json_;
  size_type position_;
  size_type error_position_;
};

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_