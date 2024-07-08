// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_
#define CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_

#include <optional>
#include <tuple>

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
#include <utility>
#include <variant>
#endif

#include "caitlyn/core/defs/core_definitions.h"

__caitlyn_begin_global_namespace

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
template <typename... Args>
using variant_t = std::variant<Args...>;

template <typename T>
using option_t = std::optional<T>;
#endif

template <typename... Args>
using tuple_t = std::tuple<Args...>;

template <typename T, typename U>
using pair_t = std::pair<T, U>;

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_UTILYTY_DEFS_UTILITY_DEFINITIONS_H_
