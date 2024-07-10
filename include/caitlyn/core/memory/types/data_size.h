// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_
#define CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_

#include "caitlyn/__detail.h"

__caitlyn_begin_global_namespace

enum class datasize_t : byte_t {
  bit,
  byte,
  kilobit,  kibibit, kilobyte,  kibibyte,
  megabit,  mebibit, megabyte,  mebibyte,
  gigabit,  gibibit, gigabyte,  gibibyt,
  terabit,  tebibit, terabyte,  tebibyt,
  petabit,  pebibit, petabyte,  pebibyte,
  exabit,   exbibit, exabyte,   exbibyte,
  zetabit,  zebibit, zetabyte,  zebibyte,
  yottabit, yobibit, yottabyte, yobibyte
};

__caitlyn_end_global_namespace

#endif // CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_