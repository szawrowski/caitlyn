// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_FORMAT_CONVERTERS_H_
#define CAITLYN_CORE_STRING_FORMAT_CONVERTERS_H_

#include <iomanip>

#include "caitlyn/core/char.h"
#include "caitlyn/core/format/types/types.h"
#include "caitlyn/core/traits/traits.h"

namespace cait {
namespace strfmt {
namespace __detail {

template <typename T>
static typename std::enable_if<std::is_integral<T>::value, std::string>::type
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
static
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

static std::string to_string(const std::string& value,
                             const format_spec_t& spec) {
  std::string str = value;
  if (static_cast<int_t>(str.size()) < spec.width) {
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

static std::string to_string(const char_t* value, const format_spec_t& spec) {
  return to_string(std::string{value}, spec);
}

template <typename T>
typename std::enable_if<has_to_string<T>::value, std::string>::type to_string(
    const T& value, const format_spec_t& spec) {
  return to_string(value.to_string(), spec);
}

}  // namespace __detail
}  // namespace strfmt
}  // namespace cait

#endif  // CAITLYN_CORE_STRING_FORMAT_CONVERTERS_H_
