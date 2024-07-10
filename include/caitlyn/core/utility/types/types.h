// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_TYPES_TYPES_H_
#define CAITLYN_CORE_UTILITY_TYPES_TYPES_H_

#include <tuple>
#include <utility>

#if __caitlyn_has_cxx17
  #include <optional>
  #include <variant>
#endif

#include "caitlyn/__detail.h"

__caitlyn_begin_global_namespace

#if __caitlyn_has_cxx17
template <typename... Args>
using variant_t = std::variant<Args...>;

template <typename T>
using option_t = std::optional<T>;
#endif

template <typename T, typename U>
using pair_t = std::pair<T, U>;

template <typename... Args>
using tuple_t = std::tuple<Args...>;

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_UTILITY_TYPES_TYPES_H_