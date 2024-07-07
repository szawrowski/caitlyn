// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_ALGO_FIND_H_
#define CAITLYN_CORE_STRING_ALGO_FIND_H_

#include "caitlyn/core/string/string.h"

BEGIN_CAITLYN_NS
BEGIN_DETAIL_NS

static vector_t<size_t> get_kmp_failure_vec(const string_t& pattern) {
  const size_t pattern_size = pattern.size();
  auto failure = vector_t<size_t>(pattern_size + 1);
  failure[0] = -1;

  for (size_t i = 0, j = failure[0]; i < pattern_size; ++i) {
    while (j != string_t::npos && pattern[j] != pattern[i]) {
      j = failure[j];
    }
    failure[i + 1] = ++j;
  }
  return failure;
}

END_DETAIL_NS

static bool_t kmp(const string_t& pattern, const string_t& text) {
  const size_t text_size = text.size();
  const size_t pattern_size = pattern.size();
  const auto failure = __detail::get_kmp_failure_vec(pattern);

  for (size_t i = 0, j = 0; i < text_size; ++i) {
    while (j != string_t::npos && pattern[j] != text[i]) {
      j = failure[j];
    }
    if (++j == pattern_size) {
      return true;
    }
  }
  return {};
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_STRING_ALGO_FIND_H_