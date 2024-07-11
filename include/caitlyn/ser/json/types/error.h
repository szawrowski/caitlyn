// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_ERROR_H_
#define CAITLYN_SER_JSON_TYPES_ERROR_H_

#include "caitlyn/ser/json/defs/defs.h"

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
