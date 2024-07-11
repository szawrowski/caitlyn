// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#include <string>

#include "caitlyn/ser/json/types/error.h"

#ifndef CAITLYN_SER_JSON_UTILITY_UTILITY_H_
#define CAITLYN_SER_JSON_UTILITY_UTILITY_H_

namespace cait {
namespace json {

static std::string get_error_string(const error_t error) {
  switch (error) {
    case error_t::no_error:
      return "No error.";
    case error_t::unterminated_string:
      return "Unterminated string.";
    case error_t::expected_string_key:
      return "Expected string key.";
    case error_t::missing_colon:
      return "Missing colon.";
    case error_t::unterminated_object:
      return "Unterminated object.";
    case error_t::unterminated_array:
      return "Unterminated array.";
    case error_t::invalid_number:
      return "Invalid number.";
    case error_t::number_conversion_error:
      return "Number conversion error.";
    case error_t::invalid_value:
      return "Invalid value.";
    case error_t::unexpected_character:
      return "Unexpected character.";
    case error_t::trailing_comma:
      return "Trailing comma.";
    case error_t::invalid_json:
      return "Invalid JSON.";
    default:
      return "Unknown error.";
  }
}

}  // namespace json
}  // namespace cait

#endif  // CAITLYN_SER_JSON_UTILITY_UTILITY_H_
