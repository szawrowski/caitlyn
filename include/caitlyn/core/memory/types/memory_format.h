// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_TYPES_MEMORY_FORMAT_H_
#define CAITLYN_CORE_MEMORY_TYPES_MEMORY_FORMAT_H_

#include "caitlyn/__detail.h"

__caitlyn_begin_global_namespace

enum class memfmt_t : byte_t {
  bit,
  byte
};

__caitlyn_end_global_namespace

#endif // CAITLYN_CORE_MEMORY_TYPES_MEMORY_FORMAT_H_
