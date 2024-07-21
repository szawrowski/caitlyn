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

#ifndef CAITLUN_CORE_TRAITS_TYPES_FORWARD_H_
#define CAITLUN_CORE_TRAITS_TYPES_FORWARD_H_

#include "caitlyn/__core/traits/types/primary.h"
#include "caitlyn/__core/traits/types/references.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
T&& forward(traits::remove_reference_t<T>& value) noexcept {
  return static_cast<T&&>(value);
}

// Версия для rvalue-ссылок
template <typename T>
T&& forward(traits::remove_reference_t<T>&& value) noexcept {
  static_assert(!is_lvalue_reference<T>(), "bad forward call");
  return static_cast<T&&>(value);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_FORWARD_H_
