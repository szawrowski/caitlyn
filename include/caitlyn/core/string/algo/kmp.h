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

#ifndef CAITLYN_CORE_STRING_ALGO_KMP_H_
#define CAITLYN_CORE_STRING_ALGO_KMP_H_

#include <string>
#include <vector>

namespace cait {
namespace __detail {

inline std::vector<size_t> get_kmp_failure_vec(const std::string& pattern) {
  const size_t pattern_size = pattern.size();
  auto failure = std::vector<size_t>(pattern_size + 1);
  failure[0] = -1;

  for (size_t i = 0, j = failure[0]; i < pattern_size; ++i) {
    while (j != std::string::npos && pattern[j] != pattern[i]) {
      j = failure[j];
    }
    failure[i + 1] = ++j;
  }
  return failure;
}

}  // namespace __detail

inline bool_t kmp(const std::string& pattern, const std::string& text) {
  const size_t text_size = text.size();
  const size_t pattern_size = pattern.size();
  const auto failure = __detail::get_kmp_failure_vec(pattern);

  for (size_t i = 0, j = 0; i < text_size; ++i) {
    while (j != std::string::npos && pattern[j] != text[i]) {
      j = failure[j];
    }
    if (++j == pattern_size) {
      return true;
    }
  }
  return {};
}

}  // namespace cait

#endif  // CAITLYN_CORE_STRING_ALGO_KMP_H_
