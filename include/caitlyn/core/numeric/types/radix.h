// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
#define CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

enum class radix_t : byte_t {
  binary = 0x2,
  octal = 0x8,
  decimal = 0xA,
  hexadecimal = 0x10,
};

static constexpr auto numeric_base_chars(const radix_t radix) {
  switch (radix) {
    case radix_t::binary:
      return "01";
    case radix_t::octal:
      return "01234567";
    case radix_t::hexadecimal:
      return "0123456789ABCDEF";
    default:
      return "0123456789";
  }
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
