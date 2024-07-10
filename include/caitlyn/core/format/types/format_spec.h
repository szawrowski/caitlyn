// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_
#define CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_

#include "caitlyn/core/format/types/format_align.h"
#include "caitlyn/core/format/types/format_type.h"

namespace cait {
namespace strfmt {

struct format_spec_t {
  format_align_t align = format_align_t::left;
  int_t width = 0;
  char_t fill = ' ';
  format_type_t type = format_type_t::string;
  int_t precision = -1;
};

}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_TYPES_FORMAT_SPEC_H_
