// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_
#define CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_

#include "caitlyn/core/char/char.h"
#include "caitlyn/core/containers.h"
#include "caitlyn/core/string/defs/string_definitions.h"

BEGIN_CAITLYN_NS

static vector_t<string_t> split(const string_t& text, const char_t delim) {
  strstream_t ss{text};
  string_t item;
  vector_t<string_t> data;

  while (std::getline(ss, item, delim)) {
    data.emplace_back(item);
  }
  return data;
}

static string_t repeat(const string_t& str, const size_t count) {
  if (count < 2) {
    return str;
  }
  strstream_t ss;
  for (size_t i = 0; i < count; ++i) {
    ss << str;
  }
  return ss.str();
}

static string_t to_uppercase(string_t value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](const char_t c) { return to_uppercase(c); });
  return value;
}

static string_t to_lowercase(string_t value) {
  std::transform(value.begin(), value.end(), value.begin(),
                 [](const char_t c) { return to_lowercase(c); });
  return value;
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_STRING_UTILITY_STRING_UTILITY_H_
