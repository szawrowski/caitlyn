// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_UTILITY_JSON_ERROR_STRINGS_H_
#define CAITLYN_SER_JSON_UTILITY_JSON_ERROR_STRINGS_H_

#include "caitlyn/ser/json/types/json_parse_error.h"
#include "caitlyn/core/string.h"

__caitlyn_begin_global_namespace

static string_t get_json_parse_error_string(
    const std::pair<json_parse_error_t, size_t>& error) {
  ostrstream_t oss;
  const auto pos_value{" (at position: )"};

  switch (error.first) {
    case json_parse_error_t::no_error:
      oss << "No error";
    return oss.str();
    case json_parse_error_t::unterminated_string:
      oss << "Unterminated string";
    break;
    case json_parse_error_t::expected_string_key:
      oss << "Expected string key";
    break;
    case json_parse_error_t::missing_colon:
      oss << "Missing colon";
    break;
    case json_parse_error_t::unterminated_object:
      oss << "Unterminated object";
    break;
    case json_parse_error_t::unterminated_array:
      oss << "Unterminated array";
    break;
    case json_parse_error_t::invalid_number:
      oss << "Invalid number";
    break;
    case json_parse_error_t::number_conversion_error:
      oss << "Number conversion error";
    break;
    case json_parse_error_t::invalid_value:
      oss << "Invalid value";
    break;
    case json_parse_error_t::unexpected_character:
      oss << "Unexpected character";
    break;
    case json_parse_error_t::trailing_comma:
      oss << "Trailing comma";
    break;
    case json_parse_error_t::invalid_json:
      oss << "Invalid JSON";
    break;
    default:
      oss << "Unknown error";
    return oss.str();
  }
  oss << pos_value << error.second;
  return oss.str();
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_SER_JSON_UTILITY_JSON_ERROR_STRINGS_H_
