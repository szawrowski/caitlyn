// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
#define CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_

#include <type_traits>
#include <utility>
#include <vector>

#include "caitlyn/core/containers/types/types.h"

namespace cait {

template <typename MapT>
std::vector<typename std::remove_reference<MapT>::type::key_type> get_map_keys(
    MapT&& map) {
  std::vector<typename std::remove_reference<MapT>::type::key_type> keys;

  for (auto& element : map) {
    keys.emplace_back(element.first);
  }
  return keys;
}

template <typename MapT>
std::vector<typename std::remove_reference<MapT>::type::mapped_type>
get_map_values(MapT&& map) {
  std::vector<typename std::remove_reference<MapT>::type::mapped_type> values;

  for (auto& element : map) {
    values.emplace_back(element.second);
  }
  return values;
}

}  // namespace cait

#endif  // CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
