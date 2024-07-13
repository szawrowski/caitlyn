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

#ifndef CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H
#define CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H

#include <type_traits>

namespace cait {

template <typename T>
class has_to_string {
private:
  template <typename U>
  static auto check(U*) -> decltype(std::declval<U>().to_string(),
                                    std::true_type());
  template <typename>
  static std::false_type check(...);

public:
  static constexpr bool value = decltype(check<T>(nullptr))::value;
};

}  // namespace cait

#endif  // CAITLYN_CORE_TRAITS_CONSTRAINTS_STRING_H
