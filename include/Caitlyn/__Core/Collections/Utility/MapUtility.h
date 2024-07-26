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

#ifndef CAITLYN_CORE_COLLECTIONS_UTILITY_MAPUTILITY_H_
#define CAITLYN_CORE_COLLECTIONS_UTILITY_MAPUTILITY_H_

#include <type_traits>
#include <vector>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename MapT>
std::vector<typename std::remove_reference<MapT>::type::key_type> GetMapKeys(MapT&& map)
{
    std::vector<typename std::remove_reference<MapT>::type::key_type> keys;

    for (auto& element : map)
    {
        keys.emplace_back(element.first);
    }
    return keys;
}

template <typename MapT>
std::vector<typename std::remove_reference<MapT>::type::mapped_type> GetMapValues(MapT&& map)
{
    std::vector<typename std::remove_reference<MapT>::type::mapped_type> values;

    for (auto& element : map)
    {
        values.emplace_back(element.second);
    }
    return values;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_COLLECTIONS_UTILITY_MAPUTILITY_H_
