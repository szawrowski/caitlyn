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

#include <bitset>

#include "caitlyn/__core/format/specifier.h"
#include "caitlyn/__core/string.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_FORMAT_NAMESPACE_BEGIN

inline void process_string_view(basic_string_t<char>& value,
                                const spec_t& spec) {
  auto to_binary = [](const basic_string_t<char>& str, const bool prefix) {
    std::ostringstream oss;
    if (prefix) {
      oss << def::digit_zero << def::latin_small_letter_b;
    }
    const auto bytes = str.c_str();
    for (size_t i = 0; i < str.byte_count(); ++i) {
      oss << std::bitset<8>(bytes[i]).to_string();
      if (i < str.byte_count() - 1) {
        oss << def::space;
      }
    }
    return oss.str();
  };
  switch (spec.repr) {
    case repr_t::binary:
      value = to_binary(value, false);
      break;
    case repr_t::binary_pref:
      value = to_binary(value, true);
      break;
    default:
      break;
  }
}

inline void process_integral_view(basic_string_t<char>& value,
                                  const spec_t& spec) {
  auto to_binary = [](const basic_string_t<char>& str, const bool prefix) {
    std::ostringstream oss;
    if (prefix) {
      oss << def::digit_zero << def::latin_small_letter_b;
    }
    oss << std::bitset<8>(std::stoll(str.str())).to_string();
    return oss.str();
  };
  switch (spec.repr) {
    case repr_t::binary:
      value = to_binary(value, false);
      break;
    case repr_t::binary_pref:
      value = to_binary(value, true);
      break;
    default:
      break;
  }
}

inline void process_floating_view(basic_string_t<char>& value,
                                  const spec_t& spec) {
  auto to_binary = [](const basic_string_t<char>& str, const bool prefix) {
    std::ostringstream oss;
    if (prefix) {
      oss << def::digit_zero << def::latin_small_letter_b;
    }
    double v = std::stod(str.str());
    const std::bitset<sizeof(double) * 8> bits{
        *reinterpret_cast<unsigned long long*>(&v)};
    oss << bits.to_string();
    return oss.str();
  };
  switch (spec.repr) {
    case repr_t::binary:
      value = to_binary(value, false);
      break;
    case repr_t::binary_pref:
      value = to_binary(value, true);
      break;
    default:
      break;
  }
}

inline void process_repr(basic_string_t<char>& value, const spec_t& spec) {
  if (spec.repr == repr_t::standard) {
    return;
  }
  switch (spec.type) {
    case value_t::integral:
      process_integral_view(value, spec);
      break;
    case value_t::floating:
      process_floating_view(value, spec);
      break;
    default:
      process_string_view(value, spec);
      break;
  }
}

inline void process_align(basic_string_t<char>& value,
                               const spec_t& spec) {
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

inline void process_spec(basic_string_t<char>& value,
                                  const spec_t& spec) {
  process_repr(value, spec);
  process_align(value, spec);
}

inline basic_string_t<char> process_string(const basic_string_t<char>& value,
                                           const spec_t& spec) {
  basic_string_t<char> result = value;
  process_spec(result, spec);
  return result;
}

inline basic_string_t<char> process_floating(const basic_string_t<char>& value,
                                             const spec_t& spec) {
  std::ostringstream oss;
  const auto dot_index = value.find(def::full_stop);

  if (dot_index != basic_string_t<char>::npos) {
    oss << value.substr(0, dot_index + 1);

    if (spec.precision > 0) {
      const size_t limit = dot_index + 1 + spec.precision;
      size_t index = dot_index + 1;

      while (index < value.size() && is_digit(value[index]) && index < limit) {
        oss << value[index];
        ++index;
      }
      while (index < limit) {
        oss << def::digit_zero;
        ++index;
      }
    }
  } else {
    oss << value;
    if (spec.precision > 0) {
      oss << def::full_stop;
      for (size_t i = 0; i < static_cast<size_t>(spec.precision); ++i) {
        oss << def::digit_zero;
      }
    }
  }
  basic_string_t<char> result = oss.str();
  process_spec(result, spec);
  return result;
}

inline basic_string_t<char> process_integral(const basic_string_t<char>& value,
                                             const spec_t& spec) {
  basic_string_t<char> result = value;
  process_spec(result, spec);
  return result;
}

inline basic_string_t<char> process(const basic_string_t<char>& value,
                                    const spec_t& spec) {
  const auto type = spec.type;

  switch (type) {
    case value_t::integral:
      return process_integral(value, spec);
    case value_t::floating:
      return process_floating(value, spec);
    default:
      return process_string(value, spec);
  }
}

__CAITLYN_FORMAT_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLYN_CORE_FORMAT_PROCESSOR_H_
