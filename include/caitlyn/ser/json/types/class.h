// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_CLASS_H_
#define CAITLYN_SER_JSON_TYPES_CLASS_H_

#include "caitlyn/ser/json/defs/defs.h"

__caitlyn_begin_global_namespace
__caitlyn_begin_json_namespace

enum class class_t {
  null,
  object,
  array,
  string,
  floating,
  integral,
  boolean
};

__caitlyn_end_json_namespace
__caitlyn_end_global_namespace

#endif  // CAITLYN_SER_JSON_TYPES_CLASS_H_
