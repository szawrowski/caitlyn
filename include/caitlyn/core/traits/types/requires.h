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

#ifndef CAITLUN_CORE_TRAITS_TYPES_REQUIRES_H_
#define CAITLUN_CORE_TRAITS_TYPES_REQUIRES_H_

namespace cait {
namespace traits {
namespace __detail {

template <bool B, typename T = void>
struct requires_impl_t {};

template <typename T>
struct requires_impl_t<true, T> {
  using type = T;
};

}  // namespace __detail
}  // namespace traits

template <bool B, typename T = void>
using requires_t = typename traits::__detail::requires_impl_t<B, T>::type;

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_REQUIRES_H_
