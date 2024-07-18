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

#ifndef CAITLYN_CORE_FORMAT_CONVERTERS_H_
#define CAITLYN_CORE_FORMAT_CONVERTERS_H_

#include <iomanip>

#include "caitlyn/core/string.h"
#include "caitlyn/core/traits.h"

namespace cait {
namespace fmt {

inline string_t str(const string_t& value) {
  string_t str = value;
  return str;
}

inline string_t str(const char* value) {
  return string_t{value};
}

template <typename T>
required_t<is_integer<T>(), string_t> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_floating<T>(), string_t> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_character<T>(), string_t> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_boolean<T>(), string_t> str(const T& value) {
  return value ? "true" : "false";
}

template <typename T>
required_t<has_to_string<T>(), string_t> str(const T& value) {
  return value.to_string();
}

template <typename T>
required_t<has_str<T>(), string_t> str(const T& value) {
  return value.str();
}

}  // namespace fmt
}  // namespace cait

#endif  // CAITLYN_CORE_FORMAT_CONVERTERS_H_
