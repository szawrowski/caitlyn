// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAILYN_CORE_TRAITS_OBJECT_H
#define CAILYN_CORE_TRAITS_OBJECT_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T>
struct has_destructor {
private:
  template <typename U>
  static std::true_type check(decltype(std::declval<U>().~U())*);

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_OBJECT_H
