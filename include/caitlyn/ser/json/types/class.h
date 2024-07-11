// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_CLASS_H_
#define CAITLYN_SER_JSON_TYPES_CLASS_H_

#include "caitlyn/ser/json/defs/defs.h"

namespace cait {
namespace json {

enum class class_t {
  null,
  object,
  array,
  string,
  floating,
  integral,
  boolean
};

}  // namespace json
}  // namespace cait

#endif  // CAITLYN_SER_JSON_TYPES_CLASS_H_
