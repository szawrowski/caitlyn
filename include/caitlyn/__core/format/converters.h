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

#include "caitlyn/__core/string.h"
#include "caitlyn/__core/traits.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_FORMAT_NAMESPACE_BEGIN

inline basic_string_t<char> str(const basic_string_t<char>& value) {
  basic_string_t<char> str = value;
  return str;
}

inline basic_string_t<char> str(const char* value) { return basic_string_t<char>{value}; }

template <typename T>
required_t<is_integer<T>(), basic_string_t<char>> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_floating<T>(), basic_string_t<char>> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_character<T>(), basic_string_t<char>> str(const T& value) {
  return std::to_string(value);
}

template <typename T>
required_t<is_boolean<T>(), basic_string_t<char>> str(const T& value) {
  return to_string(value);
}

template <typename T>
required_t<has_to_string<T>(), basic_string_t<char>> str(const T& value) {
  return value.to_string();
}

template <typename T>
required_t<has_str<T>(), basic_string_t<char>> str(const T& value) {
  return value.str();
}

__CAITLYN_FORMAT_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_CONVERTERS_H_
