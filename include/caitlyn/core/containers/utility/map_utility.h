// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
#define CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_

#include "caitlyn/core/containers/types/types.h"

namespace cait {

static auto get_map_keys = [](auto&& map) -> decltype(auto) {
  using key_type =
      typename std::remove_reference<decltype(map)>::type::key_type;
  vector_t<key_type> keys;

  for (auto& element : map) {
    keys.emplace_back(element.first);
  }
  return std::move(keys);
};

static auto get_map_values = [](auto&& map) -> decltype(auto) {
  using mapped_type =
      typename std::remove_reference<decltype(map)>::type::mapped_type;
  vector_t<mapped_type> values;

  for (auto& element : map) {
    values.emplace_back(element.second);
  }
  return std::move(values);
};

}  // namespace cait

#endif  // CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
