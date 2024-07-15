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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_CONTAINERS_H
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_CONTAINERS_H

#include "caitlyn/core/traits/types/base.h"

namespace cait {
namespace traits {

template <typename, typename = void>
struct has_begin_t : false_t {};

template <typename T>
struct has_begin_t<T, indicator_t<decltype(std::declval<T>().begin())>>
    : true_t {};

template <typename, typename = void>
struct has_end_t : false_t {};

template <typename T>
struct has_end_t<T, indicator_t<decltype(std::declval<T>().end())>> : true_t {};

template <typename, typename = void>
struct has_push_back_t : false_t {};

template <typename T>
struct has_push_back_t<T, indicator_t<decltype(std::declval<T>().push_back(
                              std::declval<typename T::value_type>()))>>
    : true_t {};

template <typename, typename = void>
struct has_pop_back_t : false_t {};

template <typename T>
struct has_pop_back_t<T, indicator_t<decltype(std::declval<T>().pop_back())>>
    : true_t {};

template <typename, typename = void>
struct has_size_t : false_t {};

template <typename T>
struct has_size_t<T, indicator_t<decltype(std::declval<T>().size())>> : true_t {
};

template <typename, typename = void>
struct has_front_t : false_t {};

template <typename T>
struct has_front_t<T, indicator_t<decltype(std::declval<T>().front())>>
    : true_t {};

template <typename, typename = void>
struct has_back_t : false_t {};

template <typename T>
struct has_back_t<T, indicator_t<decltype(std::declval<T>().back())>> : true_t {
};

template <typename, typename = void>
struct has_data_t : false_t {};

template <typename T>
struct has_data_t<T, indicator_t<decltype(std::declval<T>().data())>> : true_t {
};

template <typename, typename = void>
struct has_clear_t : false_t {};

template <typename T>
struct has_clear_t<T, indicator_t<decltype(std::declval<T>().clear())>>
    : true_t {};

template <typename, typename = void>
struct has_resize_t : false_t {};

template <typename T>
struct has_resize_t<T, indicator_t<decltype(std::declval<T>().resize(
                           std::declval<typename T::size_type>()))>> : true_t {
};

template <typename, typename = void>
struct has_empty_t : false_t {};

template <typename T>
struct has_empty_t<T, indicator_t<decltype(std::declval<T>().empty())>>
    : true_t {};

}  // namespace traits
}  // namespace cait

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_CONTAINERS_H
