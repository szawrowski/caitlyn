// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_
#define CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_

#include <optional>
#include <tuple>
#include <utility>
#include <variant>

#include "caitlyn/core/defs/core_definitions.h"

template <typename... Args>
using variant_t = std::variant<Args...>;

template <typename T>
using option_t = std::optional<T>;

template <typename... Args>
using tuple_t = std::tuple<Args...>;

template <typename T, typename U>
using pair_t = std::pair<T, U>;



#endif  // CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_
