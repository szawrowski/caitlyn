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

#ifndef CAITLUN_CORE_TRAITS_TYPES_REMOVE_CV_H_
#define CAITLUN_CORE_TRAITS_TYPES_REMOVE_CV_H_

namespace cait {
namespace traits {

template<typename T>
struct rmcv_t { using type = T; };

template<typename T>
struct rmcv_t<const T> { using type = T; };

template<typename T>
struct rmcv_t<volatile T> { using type = T; };

template<typename T>
struct rmcv_t<const volatile T> { using type = T; };

}  // namespace traits

template<typename T>
using remove_cv_t = typename traits::rmcv_t<T>::type;

}  // namespace cait

#endif  // CAITLUN_CORE_TRAITS_TYPES_REMOVE_CV_H_
