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

#ifndef CAITLYN_SER_JSON_TYPES_PARSER_H_
#define CAITLYN_SER_JSON_TYPES_PARSER_H_

#include "caitlyn/core/string.h"
#include "caitlyn/ser/json/types/data.h"
#include "caitlyn/ser/json/types/error.h"

namespace cait {
namespace json {
namespace __detail {

class parser_t {
public:
  using string_type = string_t;
  using size_type = size_t;

public:
  static parser_t parse(const string_type& json) {
    parser_t parser{json};

    if (json.empty()) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(0);
      return parser;
    }
    const auto first = find_first_nonws(json);
    const auto last = find_last_nonws(json);

    if (json[first] != get_char(ascii_t::left_curly_br)) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(first);
      return parser;
    }
    if (json[last] != get_char(ascii_t::right_curly_br)) {
      parser.set_error(error_t::invalid_json);
      parser.set_error_position(last);
      return parser;
    }
    parser.data_ = parser.parse_value();
    return parser;
  }

  __caitlyn_nodiscard bool_t has_error() const {
    return error_ != error_t::no_error;
  }

  __caitlyn_nodiscard error_t get_error() const { return error_; }

  __caitlyn_nodiscard data_t get_data() const { return data_; }

private:
  parser_t(const string_type& json)
      : error_{error_t::no_error}, json_{json}, position_{} {}

  data_t parse_value() {
    skip_ws();

    if (position_ >= json_.size()) {
      return data_t{};
    }
    const char current_char = json_[position_];

    if (current_char == get_char(ascii_t::quot_mark)) {
      return parse_string();
    }
    if (current_char == get_char(ascii_t::left_curly_br)) {
      return parse_object();
    }
    if (current_char == get_char(ascii_t::left_square_br)) {
      return parse_array();
    }
    if (current_char == get_char(ascii_t::latin_small_letter_t) ||
        current_char == get_char(ascii_t::latin_small_letter_f)) {
      return parse_boolean();
    }
    if (current_char == get_char(ascii_t::latin_small_letter_n)) {
      return parse_null();
    }
    if (std::isdigit(current_char) ||
        current_char == get_char(ascii_t::hyphen_minus) ||
        current_char == get_char(ascii_t::plus_sign)) {
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

      if (json_[position_] == get_char(ascii_t::right_curly_br)) {
        next();
        return result;
      }
      if (json_[position_] == get_char(ascii_t::quot_mark)) {
        next();
        const auto key_end =
            json_.find(get_char(ascii_t::quot_mark), position_);

        if (key_end == string_type::npos) {
          set_error(error_t::unterminated_string);
          set_error_position(position_);
          return data_t{};
        }
        string_type key = json_.substr(position_, key_end - position_);
        position_ = key_end + 1;

        skip_ws();
        if (json_[position_] != get_char(ascii_t::colon)) {
          set_error(error_t::missing_colon);
          set_error_position(position_);
          return data_t{};
        }
        next();
        skip_ws();
        result[key] = parse_value();

        skip_ws();
        if (json_[position_] == get_char(ascii_t::comma)) {
          next();
          skip_ws();

          if (json_[position_] == get_char(ascii_t::right_curly_br)) {
            set_error(error_t::trailing_comma);
            set_error_position(position_);
            return data_t{};
          }
        } else if (json_[position_] == get_char(ascii_t::right_curly_br)) {
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

      if (json_[position_] == get_char(ascii_t::right_square_br)) {
        next();
        return result;
      }
      const data_t value = parse_value();
      result.append(value);

      skip_ws();
      if (json_[position_] == get_char(ascii_t::comma)) {
        next();
        skip_ws();

        if (json_[position_] == get_char(ascii_t::right_square_br)) {
          set_error(error_t::trailing_comma);
          set_error_position(position_);
          return data_t{};
        }
      } else if (json_[position_] == get_char(ascii_t::right_square_br)) {
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
    if (json_.compare(position_, 4, get_as_string(nullptr)) == 0) {
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
           json_[position_] != get_char(ascii_t::quot_mark)) {
      if (json_[position_] == get_char(ascii_t::rev_solidus)) {
        next();
        if (position_ >= json_.size()) {
          set_error(error_t::unterminated_string);
          set_error_position(position_);
          return data_t{};
        }
        if (json_[position_] == get_char(ascii_t::quot_mark)) {
          escaped_stream << get_char(ascii_t::quot_mark);
        } else if (json_[position_] == get_char(ascii_t::rev_solidus)) {
          escaped_stream << get_char(ascii_t::rev_solidus);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_b)) {
          escaped_stream << get_char(ascii_t::backspace);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_f)) {
          escaped_stream << get_char(ascii_t::form_feed);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_n)) {
          escaped_stream << get_char(ascii_t::line_feed);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_r)) {
          escaped_stream << get_char(ascii_t::carriage_ret);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_t)) {
          escaped_stream << get_char(ascii_t::char_tab);
        } else if (json_[position_] ==
                   get_char(ascii_t::latin_small_letter_u)) {
          if (position_ + 4 >= json_.size()) {
            set_error(error_t::invalid_escape_sequence);
            set_error_position(position_);
            return data_t{};
          }
          string_type hex_code = json_.substr(position_ + 1, 4);
          try {
            const code_point_t code_point = std::stoul(hex_code, nullptr, 16);
            escaped_stream << static_cast<char_t>(code_point);
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
    if (json_[position_] == get_char(ascii_t::quot_mark)) {
      next();
      return escaped_stream.str();
    }
    set_error(error_t::unterminated_string);
    set_error_position(position_);
    return data_t{};
  }

  data_t parse_boolean() {
    if (json_.compare(position_, 4, get_as_string(true)) == 0) {
      next(4);
      return true;
    }
    if (json_.compare(position_, 5, get_as_string(false)) == 0) {
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
           (std::isdigit(json_[end_number]) ||
            json_[end_number] == get_char(ascii_t::full_stop) ||
            json_[end_number] == get_char(ascii_t::latin_small_letter_e) ||
            json_[end_number] == get_char(ascii_t::latin_cap_letter_e) ||
            json_[end_number] == get_char(ascii_t::hyphen_minus) ||
            json_[end_number] == get_char(ascii_t::plus_sign))) {
      ++end_number;
    }
    const string_type number_str =
        json_.substr(position_, end_number - position_);
    try {
      if (number_str.find(get_char(ascii_t::plus_sign)) != string_type::npos ||
          number_str.find(get_char(ascii_t::latin_small_letter_e)) !=
              string_type::npos ||
          number_str.find(get_char(ascii_t::latin_cap_letter_e)) !=
              string_type::npos) {
        result = std::stod(number_str);
      } else {
        result = std::stoll(number_str);
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
    while (position_ < json_.size() &&
           (json_[position_] == get_char(ascii_t::space) ||
            json_[position_] == get_char(ascii_t::char_tab) ||
            json_[position_] == get_char(ascii_t::line_feed) ||
            json_[position_] == get_char(ascii_t::carriage_ret))) {
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

}  // namespace __detail
}  // namespace json
}  // namespace cait

#endif  // CAITLYN_SER_JSON_TYPES_PARSER_H_