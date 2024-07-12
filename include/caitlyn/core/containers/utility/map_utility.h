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

#ifndef CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_
#define CAITLYN_CORE_CONTAINERS_UTILITY_MAP_UTILITY_H_

#include <type_traits>
#include <vector>

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
