// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
#define CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_

#include "caitlyn/core/containers/defs/container_definitions.h"

BEGIN_CAITLYN_NS

static auto get_map_keys = [](auto&& map) -> decltype(auto) {
  using key_type = typename std::remove_reference_t<decltype(map)>::key_type;
  vector_t<key_type> keys;

  for (auto& [key, _dummy] : map) {
    keys.emplace_back(key);
  }
  return std::move(keys);
};

static auto get_map_values = [](auto&& map) -> decltype(auto) {
  using value_type =
      typename std::remove_reference_t<decltype(map)>::mapped_type;
  vector_t<value_type> values;

  for (auto& [_dummy, value] : map) {
    values.emplace_back(value);
  }
  return std::move(values);
};

END_CAITLYN_NS

#endif  // CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
