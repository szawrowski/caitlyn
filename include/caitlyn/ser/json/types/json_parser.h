// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_PARSER_H_
#define CAITLYN_SER_JSON_TYPES_JSON_PARSER_H_

#include "caitlyn/core/string.h"
#include "caitlyn/ser/json/types/json_data.h"
#include "caitlyn/ser/json/types/json_parse_error.h"

BEGIN_CAITLYN_NS
BEGIN_DETAIL_NS

class json_parser_t {
public:
  using string_type = string_t;
  using size_type = size_t;

public:
  static json_parser_t parse(const string_type& json) {
    json_parser_t parser{json};

    if (json.empty()) {
      parser.set_error(json_parse_error_t::invalid_json);
      parser.set_error_position(0);
      return parser;
    }
    const auto first = find_first_nonws(json);
    const auto last = find_last_nonws(json);

    if (json[first] != get_symbol(char_hex_t::opening_curly_bracket)) {
      parser.set_error(json_parse_error_t::invalid_json);
      parser.set_error_position(first);
      return parser;
    }
    if (json[last] != get_symbol(char_hex_t::closing_curly_bracket)) {
      parser.set_error(json_parse_error_t::invalid_json);
      parser.set_error_position(last);
      return parser;
    }
    parser.data_ = parser.parse_value();
    return parser;
  }

  [[nodiscard]] bool_t has_error() const {
    return error_ != json_parse_error_t::no_error;
  }

  [[nodiscard]] pair_t<json_parse_error_t, size_t> get_error() const {
    return std::make_pair(error_, error_position_);
  }

  [[nodiscard]] json_data_t get_data() const { return data_; }

private:
  json_parser_t(const string_type& json)
      : error_{json_parse_error_t::no_error}, json_{json}, position_{} {}

  json_data_t parse_value() {
    skip_ws();

    if (position_ >= json_.size()) {
      return json_data_t{};
    }
    switch (json_[position_]) {
      case get_symbol(char_hex_t::double_quote):
        return parse_string();
      case get_symbol(char_hex_t::opening_curly_bracket):
        return parse_object();
      case get_symbol(char_hex_t::opening_square_bracket):
        return parse_array();
      case get_symbol(char_hex_t::lowercase_t):
      case get_symbol(char_hex_t::lowercase_f):
        return parse_boolean();
      case get_symbol(char_hex_t::lowercase_n):
        return parse_null();
      default:
        if (std::isdigit(json_[position_]) ||
            json_[position_] == get_symbol(char_hex_t::minus) ||
            json_[position_] == get_symbol(char_hex_t::plus)) {
          return parse_number();
        }
        set_error(json_parse_error_t::unexpected_character);
        set_error_position(position_);
        return json_data_t{};
    }
  }

  json_data_t parse_object() {
    json_data_t result = json::make_object();
    next();
    skip_ws();

    while (position_ < json_.size()) {
      skip_ws();

      if (json_[position_] == get_symbol(char_hex_t::closing_curly_bracket)) {
        next();
        return result;
      }
      if (json_[position_] == get_symbol(char_hex_t::double_quote)) {
        next();
        const auto key_end =
            json_.find(get_symbol(char_hex_t::double_quote), position_);

        if (key_end == string_type::npos) {
          set_error(json_parse_error_t::unterminated_string);
          set_error_position(position_);
          return json_data_t{};
        }
        string_type key = json_.substr(position_, key_end - position_);
        position_ = key_end + 1;

        skip_ws();
        if (json_[position_] != get_symbol(char_hex_t::colon)) {
          set_error(json_parse_error_t::missing_colon);
          set_error_position(position_);
          return json_data_t{};
        }
        next();
        skip_ws();
        result[key] = parse_value();

        skip_ws();
        if (json_[position_] == get_symbol(char_hex_t::comma)) {
          next();
          skip_ws();

          if (json_[position_] ==
              get_symbol(char_hex_t::closing_curly_bracket)) {
            set_error(json_parse_error_t::trailing_comma);
            set_error_position(position_);
            return json_data_t{};
          }
        } else if (json_[position_] ==
                   get_symbol(char_hex_t::closing_curly_bracket)) {
          next();
          return result;
        } else {
          set_error(json_parse_error_t::unexpected_character);
          set_error_position(position_);
          return json_data_t{};
        }
      } else {
        set_error(json_parse_error_t::unexpected_character);
        set_error_position(position_);
        return json_data_t{};
      }
    }
    set_error(json_parse_error_t::unterminated_object);
    set_error_position(position_);
    return json_data_t{};
  }

  json_data_t parse_array() {
    json_data_t result = json::make_array();
    next();
    skip_ws();

    while (position_ < json_.size()) {
      skip_ws();

      if (json_[position_] == get_symbol(char_hex_t::closing_square_bracket)) {
        next();
        return result;
      }
      const json_data_t value = parse_value();
      result.append(value);

      skip_ws();
      if (json_[position_] == get_symbol(char_hex_t::comma)) {
        next();
        skip_ws();

        if (json_[position_] ==
            get_symbol(char_hex_t::closing_square_bracket)) {
          set_error(json_parse_error_t::trailing_comma);
          set_error_position(position_);
          return json_data_t{};
        }
      } else if (json_[position_] ==
                 get_symbol(char_hex_t::closing_square_bracket)) {
        next();
        return result;
      } else {
        set_error(json_parse_error_t::unexpected_character);
        error_position_ = position_;
        return json_data_t{};
      }
    }
    set_error(json_parse_error_t::unterminated_array);
    set_error_position(position_);
    return json_data_t{};
  }

  json_data_t parse_null() {
    if (json_.compare(position_, 4, get_as_string(nullptr)) == 0) {
      next(4);
      return json::make_null();
    }
    set_error(json_parse_error_t::invalid_value);
    set_error_position(position_);
    return json_data_t{};
  }

  json_data_t parse_string() {
    next();
    std::ostringstream escaped_stream;

    while (position_ < json_.size() &&
           json_[position_] != get_symbol(char_hex_t::double_quote)) {
      if (json_[position_] == get_symbol(char_hex_t::backslash)) {
        next();
        if (position_ >= json_.size()) {
          set_error(json_parse_error_t::unterminated_string);
          set_error_position(position_);
          return json_data_t{};
        }
        if (json_[position_] == get_symbol(char_hex_t::double_quote)) {
          escaped_stream << get_symbol(char_hex_t::double_quote);
        } else if (json_[position_] == get_symbol(char_hex_t::backslash)) {
          escaped_stream << get_symbol(char_hex_t::backslash);
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_b)) {
          escaped_stream << get_symbol(char_hex_t::backspace);
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_f)) {
          escaped_stream << get_symbol(char_hex_t::form_feed);
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_n)) {
          escaped_stream << get_symbol(char_hex_t::line_feed);
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_r)) {
          escaped_stream << get_symbol(char_hex_t::carriage_return);
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_t)) {
          escaped_stream << get_symbol(char_hex_t::horizontal_tab);
          ;
        } else if (json_[position_] == get_symbol(char_hex_t::lowercase_u)) {
          if (position_ + 4 >= json_.size()) {
            set_error(json_parse_error_t::invalid_escape_sequence);
            set_error_position(position_);
            return json_data_t{};
          }
          string_type hex_code = json_.substr(position_ + 1, 4);
          try {
            const code_point_t code_point = std::stoul(hex_code, nullptr, 16);
            escaped_stream << static_cast<char_t>(code_point);
          } catch (const std::exception&) {
            set_error(json_parse_error_t::invalid_escape_sequence);
            set_error_position(position_);
            return json_data_t{};
          }
          position_ += 4;
        } else {
          set_error(json_parse_error_t::invalid_escape_sequence);
          set_error_position(position_);
          return json_data_t{};
        }
        next();
      } else {
        escaped_stream << json_[position_];
      }
      next();
    }
    if (json_[position_] == get_symbol(char_hex_t::double_quote)) {
      next();
      return escaped_stream.str();
    }
    set_error(json_parse_error_t::unterminated_string);
    set_error_position(position_);
    return json_data_t{};
  }

  json_data_t parse_boolean() {
    if (json_.compare(position_, 4, get_as_string(true)) == 0) {
      next(4);
      return true;
    }
    if (json_.compare(position_, 5, get_as_string(false)) == 0) {
      next(5);
      return false;
    }
    set_error(json_parse_error_t::invalid_value);
    set_error_position(position_);
    return json_data_t{};
  }

  json_data_t parse_number() {
    json_data_t result;
    auto end_number = position_;
    while (end_number < json_.size() &&
           (std::isdigit(json_[end_number]) ||
            json_[end_number] == get_symbol(char_hex_t::point) ||
            json_[end_number] == get_symbol(char_hex_t::lowercase_e) ||
            json_[end_number] == get_symbol(char_hex_t::capital_e) ||
            json_[end_number] == get_symbol(char_hex_t::minus) ||
            json_[end_number] == get_symbol(char_hex_t::plus))) {
      ++end_number;
    }
    const string_type number_str =
        json_.substr(position_, end_number - position_);
    try {
      if (number_str.find(get_symbol(char_hex_t::plus)) != string_type::npos ||
          number_str.find(get_symbol(char_hex_t::lowercase_e)) !=
              string_type::npos ||
          number_str.find(get_symbol(char_hex_t::capital_e)) !=
              string_type::npos) {
        result = std::stod(number_str);
      } else {
        result = std::stoll(number_str);
      }
    } catch (const std::out_of_range&) {
      set_error(json_parse_error_t::out_of_range_error);
      set_error_position(position_);
      return json_data_t{};
    } catch (const std::exception&) {
      set_error(json_parse_error_t::invalid_number);
      set_error_position(position_);
      return json_data_t{};
    }
    position_ = end_number;
    return result;
  }

  void skip_ws() {
    while (position_ < json_.size() &&
           (json_[position_] == get_symbol(char_hex_t::space) ||
            json_[position_] == get_symbol(char_hex_t::horizontal_tab) ||
            json_[position_] == get_symbol(char_hex_t::line_feed) ||
            json_[position_] == get_symbol(char_hex_t::carriage_return))) {
      next();
    }
  }

  void next(const size_type count = 1) { position_ += count; }

  void set_error(const json_parse_error_t error) { error_ = error; }

  void set_error_position(const size_type position) {
    error_position_ = position;
  }

private:
  json_data_t data_;
  json_parse_error_t error_;
  const string_type& json_;
  size_type position_;
  size_type error_position_;
};

END_DETAIL_NS
END_CAITLYN_NS

#endif  // CAITLYN_SER_JSON_TYPES_JSON_PARSER_H_