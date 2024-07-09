// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_PARSE_ERROR_H_
#define CAITLYN_SER_JSON_TYPES_PARSE_ERROR_H_

#include "caitlyn/ser/json/defs/defs.h"

__caitlyn_begin_global_namespace
__caitlyn_begin_json_namespace

enum class parse_error_t {
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

__caitlyn_end_json_namespace
__caitlyn_end_global_namespace

#endif  // CAITLYN_SER_JSON_TYPES_PARSE_ERROR_H_
