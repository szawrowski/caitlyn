// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_PARSE_ERROR_H_
#define CAITLYN_SER_JSON_TYPES_JSON_PARSE_ERROR_H_

#include "caitlyn/ser/defs/global_definitions.h"

BEGIN_CAITLYN_NS

enum class json_parse_error_t {
  no_error,
  unterminated_string,
  expected_string_key,
  missing_colon,
  unterminated_object,
  unterminated_array,
  invalid_number,
  number_conversion_error,
  invalid_value,
  unexpected_character,
  out_of_range_error,
  invalid_escape_sequence,
  trailing_comma,
  invalid_json
};

END_CAITLYN_NS

#endif  // CAITLYN_SER_JSON_TYPES_JSON_PARSE_ERROR_H_