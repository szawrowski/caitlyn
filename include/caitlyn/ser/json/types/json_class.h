// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_CLASS_H_
#define CAITLYN_SER_JSON_TYPES_JSON_CLASS_H_

#include "caitlyn/ser/defs/serializing_definitions.h"

__caitlyn_begin_global_namespace

enum class json_class_t {
  null,
  object,
  array,
  string,
  floating,
  integral,
  boolean
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_SER_JSON_TYPES_JSON_CLASS_H_
