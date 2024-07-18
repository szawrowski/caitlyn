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

#ifndef CAITLYN_CORE_FORMAT_PROCESSOR_H_
#define CAITLYN_CORE_FORMAT_PROCESSOR_H_

#include "caitlyn/core/string.h"
#include "caitlyn/core/format/parser.h"

namespace cait {
namespace fmt {

inline void process_alignment(string_t& value, const spec_t& spec) {
  if (value.size() >= spec.width) {
    return;
  }
  switch (spec.align) {
    case align_t::left:
      value.append(spec.width - value.size(), spec.fill);
    break;
    case align_t::right:
      value.insert(0, spec.width - value.size(), spec.fill);
    break;
    case align_t::center: {
      const size_t padding = spec.width - value.size();
      value.insert(0, padding / 2, spec.fill);
      value.append(padding - padding / 2, spec.fill);
      break;
    }
  }
}

inline string_t process_string(const string_t& value, const spec_t& spec) {
  string_t str = value;
  process_alignment(str, spec);
  return str;
}

inline string_t process_floating(const string_t& value, const spec_t& spec) {
  std::ostringstream oss;
  const auto dot_index = value.find(".");

  if (dot_index != string_t::npos) {
    oss << value.substr(0, dot_index + 1);

    if (spec.precision > 0) {
      const size_t limit = dot_index + 1 + spec.precision;
      size_t index = dot_index + 1;

      while (index < value.size() && fmt::is_digit(value[index]) && index < limit) {
        oss << value[index];
        ++index;
      }
      while (index < limit) {
        oss << '0';
        ++index;
      }
    }
  } else {
    oss << value;
    if (spec.precision > 0) {
      oss << '.';
      for (size_t i = 0; i < static_cast<size_t>(spec.precision); ++i) {
        oss << '0';
      }
    }
  }
  string_t result = oss.str();
  process_alignment(result, spec);
  return result;
}

inline string_t process_integral(const string_t& value, const spec_t& spec) {
  string_t result = value;
  process_alignment(result, spec);
  return result;
}

}  // namespace fmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_PROCESSOR_H_
