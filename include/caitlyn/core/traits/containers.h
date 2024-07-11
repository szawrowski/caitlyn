// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

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
