// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
#define CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_

#include "caitlyn/__detail.h"

namespace cait {

enum class radix_t : byte_t {
  binary = 0x2,
  octal = 0x8,
  decimal = 0xA,
  hexadecimal = 0x10,
};

}  // namespace cait

#endif  // CAITLYN_CORE_NUMERIC_TYPES_RADIX_H_
