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

#ifndef CAILYN_CORE_TRAITS_OBJECT_H
#define CAILYN_CORE_TRAITS_OBJECT_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T>
struct has_destructor {
private:
  template <typename U>
  static std::true_type check(decltype(std::declval<U>().~U())*);

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_OBJECT_H
