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

#ifndef CAITLUN_CORE_TRAITS_TYPES_FLOATING_H_
#define CAITLUN_CORE_TRAITS_TYPES_FLOATING_H_

#include "caitlyn/base.h"
#include "caitlyn/core/traits/types/bool_constant.h"
#include "caitlyn/core/traits/types/requires.h"

namespace cait {

template <typename T>
struct floating_t {
private:
  template <typename U>
  static auto check(U*)
      -> requires_t<std::is_floating_point<U>::value, true_t>;

  template <typename>
  static false_t check(...);

public:
  static constexpr bool_t value = decltype(check<T>(nullptr))::value;
};

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_FLOATING_H_
