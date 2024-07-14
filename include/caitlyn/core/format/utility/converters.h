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

#include <iomanip>
#include <sstream>

#include "caitlyn/base.h"
#include "caitlyn/core/format/types.h"
#include "caitlyn/core/traits.h"

namespace cait {
namespace strfmt {
namespace __detail {

template <typename T>
typename std::enable_if<std::is_integral<T>::value, std::string>::type
to_string(const T& value, const format_spec_t& spec) {
  std::ostringstream oss;
  oss << std::fixed << std::setprecision(0);

  if (spec.type == format_type_t::integral) {
    oss << static_cast<int64_t>(value);
  } else {
    oss << value;
  }
  std::string str = oss.str();

  if (static_cast<int>(str.size()) < spec.width) {
    switch (spec.align) {
      case format_align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case format_align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case format_align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

template <typename T>
typename std::enable_if<std::is_floating_point<T>::value, std::string>::type
to_string(const T& value, const format_spec_t& spec) {
  std::ostringstream oss;
  oss << std::fixed
      << std::setprecision(spec.precision >= 0 ? spec.precision : 6);

  oss << (spec.type == format_type_t::floating_point
              ? static_cast<float64_t>(value)
              : value);

  std::string str = oss.str();

  if (static_cast<ssize_t>(str.size()) < spec.width) {
    switch (spec.align) {
      case format_align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case format_align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case format_align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

inline std::string to_string(const std::string& value,
                             const format_spec_t& spec) {
  std::string str = value;

  if (static_cast<int>(str.size()) < spec.width) {
    switch (spec.align) {
      case format_align_t::left:
        str.append(spec.width - str.size(), spec.fill);
        break;
      case format_align_t::right:
        str.insert(0, spec.width - str.size(), spec.fill);
        break;
      case format_align_t::center: {
        const size_t padding = spec.width - str.size();
        str.insert(0, padding / 2, spec.fill);
        str.append(padding - padding / 2, spec.fill);
        break;
      }
    }
  }
  return str;
}

inline std::string to_string(const char* value, const format_spec_t& spec) {
  return to_string(std::string{value}, spec);
}

template <typename T>
required_t<convertible_to_string<T>(), std::string> to_string(
    const T& value, const format_spec_t& spec) {
  return to_string(value.to_string(), spec);
}

template <typename T>
required_t<has_str<T>(), std::string> to_string(const T& value,
                                                const format_spec_t& spec) {
  return to_string(value.str(), spec);
}

}  // namespace __detail
}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_UTILITY_CONVERTERS_H_
