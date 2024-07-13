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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H

#include <type_traits>

namespace cait {

template <typename T>
class has_less_operator {
private:
  template <typename U>
  static auto check(U*) -> decltype(std::declval<U>() < std::declval<U>(),
                                    std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

template <typename T>
class has_greater_operator {
private:
  template <typename U>
  static auto check(U*) -> decltype(std::declval<U>() > std::declval<U>(),
                                    std::true_type());
  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

template <typename T, typename U>
class has_add_operator {
private:
  template <typename A, typename B>
  static auto check(U*) -> decltype(std::declval<A>() + std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_subtract_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() - std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_multiply_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() * std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_divide_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() / std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_equal_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() == std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_not_equal_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() != std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_subscript_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>()[std::declval<B>()],
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T>
class has_increment_operator {
private:
  template <typename U>
  static auto check(U*) -> decltype(++std::declval<U&>(), std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

template <typename T>
class has_decrement_operator {
private:
  template <typename U>
  static auto check(U*) -> decltype(--std::declval<U&>(), std::true_type());

  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

template <typename T, typename U>
class has_bitwise_and_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() & std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_bitwise_or_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() | std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_bitwise_xor_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() ^ std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_left_shift_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() << std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_right_shift_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() >> std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

template <typename T, typename U>
class has_modulus_operator {
private:
  template <typename A, typename B>
  static auto check(A*) -> decltype(std::declval<A>() % std::declval<B>(),
                                    std::true_type());
  template <typename, typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T, U>(nullptr))::value;
};

}  // namespace cait

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_OPERATORS_H
