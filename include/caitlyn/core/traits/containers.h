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

#ifndef CAILYN_CORE_TRAITS_CONTAINERS_H
#define CAILYN_CORE_TRAITS_CONTAINERS_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T>
class has_begin {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().begin(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_end {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().end(), std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_push_back {
private:
  template <typename U>
  static auto check(int)
      -> decltype(std::declval<U>().push_back(
                      std::declval<typename U::value_type>()),
                  std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_pop_back {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().pop_back(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_size {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().size(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_front {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().front(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_back {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().back(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_data {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().data(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_clear {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().clear(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_resize {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().resize(
                                         std::declval<typename U::size_type>()),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_empty {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().empty(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_CONTAINERS_H
