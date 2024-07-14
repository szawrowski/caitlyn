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

#ifndef CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_
#define CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_

#include "caitlyn/core/format/types/format_align.h"
#include "caitlyn/core/format/types/format_type.h"

namespace cait {
namespace strfmt {

struct format_spec_t {
  format_align_t align = format_align_t::left;
  int width = 0;
  char fill = ' ';
  format_type_t type = format_type_t::string;
  int precision = -1;
};

}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_
