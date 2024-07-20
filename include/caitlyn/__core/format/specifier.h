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

#ifndef CAITLYN_CORE_FORMAT_TYPES_SPECIFIER_H_
#define CAITLYN_CORE_FORMAT_TYPES_SPECIFIER_H_

#include "caitlyn/__core/string.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_FORMAT_NAMESPACE_BEGIN

enum class align_t { left, right, center };
enum class value_t { string, integral, floating };

enum class repr_t {
  standard,
  binary,
  binary_pref,
  octal,
  octal_pref,
  hex,
  hex_pref
};

struct spec_t {
  align_t align = align_t::left;
  size_t width = 0;
  basic_string_t<char> fill = def::space;
  repr_t repr = repr_t::standard;
  value_t type = value_t::string;
  int precision = -1;
};

__CAITLYN_FORMAT_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_TYPES_SPECIFIER_H_
