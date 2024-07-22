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

#ifndef CAITLYN_CORE_CHAR_H_
#define CAITLYN_CORE_CHAR_H_

#include <cctype>
#include <cwchar>
#include <cwctype>
#include <cuchar>
#include <cstring>

#include "caitlyn/__core/char/defs.h"
#include "caitlyn/__core/char/types.h"
#include "caitlyn/__core/char/utility.h"

#if __CAITLYN_HAS_CXX17
  #include <charconv>
#endif

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

using character = basic_character_t<char>;

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_CHAR_H_