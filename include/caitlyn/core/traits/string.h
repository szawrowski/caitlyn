// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAILYN_CORE_TRAITS_STRING_H
#define CAILYN_CORE_TRAITS_STRING_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T>
class has_to_string {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>().to_string(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_STRING_H
