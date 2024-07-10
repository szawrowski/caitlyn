// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAILYN_CORE_TRAITS_TRAITS_H
#define CAILYN_CORE_TRAITS_TRAITS_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T, typename U>
class has_equal_operator {
private:
  template <typename X, typename Y>
  static auto check(int) -> decltype(std::declval<X>() == std::declval<Y>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T>
class has_to_string {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().to_string(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool_t value = decltype(check<T>(0))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_TRAITS_H
