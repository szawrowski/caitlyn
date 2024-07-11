// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAILYN_CORE_TRAITS_OPERATORS_H
#define CAILYN_CORE_TRAITS_OPERATORS_H

#include <type_traits>

#include "caitlyn/__detail.h"

namespace cait {

template <typename T>
class has_less_operator {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>() < std::declval<U>(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_greater_operator {
private:
  template <typename U>
  static auto check(int) -> decltype(std::declval<U>() > std::declval<U>(),
                                     std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T, typename U>
class has_add_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() + std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_subtract_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() - std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_multiply_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() * std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_divide_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() / std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_equal_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() == std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_not_equal_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() != std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_subscript_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>()[std::declval<B>()],
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T>
class has_increment_operator {
private:
  template <typename U>
  static auto check(int) -> decltype(++std::declval<U&>(), std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T>
class has_decrement_operator {
private:
  template <typename U>
  static auto check(int) -> decltype(--std::declval<U&>(), std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(0))::value;
};

template <typename T, typename U>
class has_bitwise_and_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() & std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_bitwise_or_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() | std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_bitwise_xor_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() ^ std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_left_shift_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() << std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_right_shift_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() >> std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

template <typename T, typename U>
class has_modulus_operator {
private:
  template <typename A, typename B>
  static auto check(int) -> decltype(std::declval<A>() % std::declval<B>(),
                                     std::true_type());

  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(0))::value;
};

}  // namespace cait

#endif  // CAILYN_CORE_TRAITS_OPERATORS_H
