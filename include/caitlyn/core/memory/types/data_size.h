/**
 * This file is part of the Caitlyn library
 * Copyright (C) 2024 Alexander Szawrowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_
#define CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_

#include "caitlyn/__base.h"

namespace cait {

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

}  // namespace cait

#endif // CAITLYN_CORE_MEMORY_TYPES_DATA_SIZE_H_
