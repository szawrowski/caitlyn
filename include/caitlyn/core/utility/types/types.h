// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_TYPES_TYPES_H_
#define CAITLYN_CORE_UTILITY_TYPES_TYPES_H_

#include <tuple>
#include <utility>

#if __caitlyn_has_cxx17
  #include <any>
  #include <optional>
  #include <variant>
#endif

#include "caitlyn/__detail.h"

namespace cait {

#if __caitlyn_has_cxx17
using any_t = std::any;

template <typename... Args>
using variant_t = std::variant<Args...>;

template <typename T>
using option_t = std::optional<T>;
#endif

template <typename T, typename U>
using pair_t = std::pair<T, U>;

template <typename... Args>
using tuple_t = std::tuple<Args...>;

}  // namespace cait

#endif  // CAITLYN_CORE_UTILITY_TYPES_TYPES_H_
