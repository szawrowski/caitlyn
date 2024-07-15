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

#ifndef CAITLUN_CORE_TRAITS_TYPES_REQUIRED_H_
#define CAITLUN_CORE_TRAITS_TYPES_REQUIRED_H_

namespace cait {

template<bool, typename = void>
struct constraint_t {};

template<typename Ret>
struct constraint_t<true, Ret> {
  using type = Ret;
};

template <bool Condition, typename Ret = void>
using required_t = typename constraint_t<Condition, Ret>::type;

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_REQUIRED_H_
