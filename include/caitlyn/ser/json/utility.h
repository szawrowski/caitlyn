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

#include <string>

#include "caitlyn/ser/json/types/error.h"

#ifndef CAITLYN_SER_JSON_UTILITY_H_
#define CAITLYN_SER_JSON_UTILITY_H_

namespace cait {
namespace json {

inline std::string get_error_string(const error_t error) {
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

#endif  // CAITLYN_SER_JSON_UTILITY_H_
