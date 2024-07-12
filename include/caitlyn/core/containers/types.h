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

#ifndef CAITLYN_CORE_CONTAINERS_TYPES_H_
#define CAITLYN_CORE_CONTAINERS_TYPES_H_

#include <array>
#include <deque>
#include <forward_list>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>

#include "caitlyn/base.h"

namespace cait {

// Sequence containers
template <typename T, size_t N>
using array_t = std::array<T, N>;

template <typename T>
using vector_t = std::vector<T>;
using bvector_t = std::vector<bool_t>;

template <typename T>
using deque_t = std::deque<T>;

template <typename T>
using flist_t = std::forward_list<T>;

template <typename T>
using list_t = std::list<T>;

// Associative containers
template <typename K>
using set_t = std::set<K>;

template <typename K>
using mulset_t = std::multiset<K>;

template <typename K, typename V>
using map_t = std::map<K, V>;

template <typename K, typename V>
using mulmap_t = std::multimap<K, V>;

// Unordered associative containers
template <typename K>
using uset_t = std::unordered_set<K>;

template <typename K>
using umulset_t = std::unordered_multiset<K>;

template <typename K, typename V>
using umap_t = std::unordered_map<K, V>;

template <typename K, typename V>
using umulmap_t = std::unordered_multimap<K, V>;

// Container adaptors
template <typename T>
using stack_t = std::stack<T>;

template <typename T>
using queue_t = std::queue<T>;

template <typename T>
using prqueue_t = std::priority_queue<T>;

}  // namespace cait

#endif  // CAITLYN_CORE_CONTAINERS_TYPES_H_
