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

#ifndef CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_
#define CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_

#include "caitlyn/__core/traits/types/base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

template <typename T>
auto try_add_pointer(T*)
    -> type_identity_t<typename std::remove_reference<T>::type*>;

template <typename T>
auto try_add_pointer(...) -> type_identity_t<T>;

template <typename T>
struct remove_pointer_t {
  using type = T;
};

template <typename T>
struct remove_pointer_t<T*> {
  using type = T;
};

template <typename T>
struct remove_pointer_t<T* const> {
  using type = T;
};

template <typename T>
struct remove_pointer_t<T* volatile> {
  using type = T;
};

template <typename T>
struct remove_pointer_t<T* const volatile> {
  using type = T;
};

__CAITLYN_DETAIL_NAMESPACE_END

template <typename T>
using add_pointer_t =
    typename decltype(__detail::try_add_pointer<T>(nullptr))::type;

template <typename T>
using remove_pointer_t = typename __detail::remove_pointer_t<T>::type;

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_POINTERS_H_
