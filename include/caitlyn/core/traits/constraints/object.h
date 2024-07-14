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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_OBJECT_H
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_OBJECT_H

#include "caitlyn/core/traits/types/bool_constant.h"
#include "caitlyn/core/traits/types/void.h"

namespace cait {
namespace traits {

template <typename, typename = void>
struct has_destructor_t : false_t {};

template <typename T>
struct has_destructor_t<T, void_t<decltype(std::declval<T>().~T())>> : true_t {
};

}  // namespace traits

template <typename T>
constexpr bool is_destructible() {
  return traits::has_destructor_t<T>::value;
}

}  // namespace cait

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_OBJECT_H
