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
