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

#ifndef CAITLYN_CORE_FORMAT_UTILITY_CONVERTERS_H_
#define CAITLYN_CORE_FORMAT_UTILITY_CONVERTERS_H_

#include <caitlyn/core/string/utility.h>

#include <iomanip>
#include <sstream>

#include "caitlyn/__base.h"
#include "caitlyn/core/format/types.h"
#include "caitlyn/core/string.h"
#include "caitlyn/core/traits.h"

namespace cait {
namespace strfmt {
namespace __detail {

inline void process_spec(const spec_t& spec, string_t& str) {
  switch (spec.align) {
    case align_t::left:
      str.append(spec.width - str.size(), spec.fill);
      break;
    case align_t::right:
      str.insert(0, spec.width - str.size(), spec.fill);
      break;
    case align_t::center: {
      const size_t padding = spec.width - str.size();
      str.insert(0, padding / 2, spec.fill);
      str.append(padding - padding / 2, spec.fill);
      break;
    }
  }
}

template <typename T>
required_t<is_integer<T>(), string_t> to_string(const T& value,
                                                const spec_t& spec) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(0);

  if (spec.type == type_t::integral) {
    oss << static_cast<int64_t>(value);
  } else {
    oss << value;
  }
  string_t str = oss.str();

  if (str.size() < spec.width) {
    process_spec(spec, str);
  }
  return str;
}

template <typename T>
required_t<is_floating<T>(), string_t> to_string(const T& value,
                                                 const spec_t& spec) {
  std::ostringstream oss;
  oss << std::fixed
      << std::setprecision(spec.precision >= 0 ? spec.precision : 6);

  oss << (spec.type == type_t::floating_point ? static_cast<float64_t>(value)
                                              : value);

  string_t str = oss.str();

  if (str.size() < spec.width) {
    process_spec(spec, str);
  }
  return str;
}

inline string_t to_string(const string_t& value, const spec_t& spec) {
  string_t str = value;

  if (str.size() < spec.width) {
    process_spec(spec, str);
  }
  return str;
}

// inline std::string to_string(const char* value, const spec_t& spec) {
//   return to_string(std::string{value}, spec);
// }

template <typename T>
required_t<has_to_string<T>(), string_t> to_string(const T& value,
                                                   const spec_t& spec) {
  return to_string(value.to_string(), spec);
}

template <typename T>
required_t<has_str<T>(), string_t> to_string(const T& value,
                                             const spec_t& spec) {
  return to_string(value.str(), spec);
}

template <typename T>
required_t<is_character<T>(), string_t> to_string(const T& value,
                                                  const spec_t& spec) {
  return to_string(value, spec);
}

template <typename T>
required_t<is_boolean<T>(), string_t> to_string(const T& value,
                                                const spec_t& spec) {
  return to_string(get_as_string(value), spec);
}

}  // namespace __detail
}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_UTILITY_CONVERTERS_H_
