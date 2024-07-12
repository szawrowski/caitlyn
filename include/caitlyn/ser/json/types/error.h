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

#ifndef CAITLYN_SER_JSON_TYPES_ERROR_H_
#define CAITLYN_SER_JSON_TYPES_ERROR_H_

namespace cait {
namespace json {

enum class error_t {
  no_error,
  unexpected_character,
  unterminated_string,
  unterminated_object,
  unterminated_array,
  expected_string_key,
  missing_colon,
  invalid_json,
  invalid_value,
  invalid_number,
  invalid_escape_sequence,
  number_conversion_error,
  out_of_range_error,
  trailing_comma
};

}  // namespace json
}  // namespace cait

#endif  // CAITLYN_SER_JSON_TYPES_ERROR_H_
