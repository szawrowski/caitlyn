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

#ifndef CAITLYN_CORE_UNICODE_TYPES_H_
#define CAITLYN_CORE_UNICODE_TYPES_H_

#include "caitlyn/core/unicode/types/char.h"
#include "caitlyn/core/unicode/types/string.h"

namespace cait {

using unichar_t = unicode_char<char_t>;
using unistring_t = unicode_string<unicode_char<char_t>>;

}  // namespace cait

#endif  // CAITLYN_CORE_UNICODE_TYPES_H_
