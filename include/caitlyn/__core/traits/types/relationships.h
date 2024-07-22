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

#ifndef CAITLUN_CORE_TRAITS_TYPES_RELATIONSHIPS_H_
#define CAITLUN_CORE_TRAITS_TYPES_RELATIONSHIPS_H_

#include "caitlyn/__core/traits/types/base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <typename, typename>
struct is_same_t : false_t {};

template <typename T>
struct is_same_t<T, T> : true_t {};

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_RELATIONSHIPS_H_
