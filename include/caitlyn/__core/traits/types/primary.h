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

#ifndef CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_
#define CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_

#include "caitlyn/__core/traits/types/specifiers.h"
#include "caitlyn/__core/traits/types/relationships.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_TRAITS_NAMESPACE_BEGIN

template <class T>
struct is_void_t : is_same_t<void, remove_cv_t<T>>::type {};

template <class T>
struct is_null_pointer_t : is_same_t<std::nullptr_t, remove_cv_t<T>>::type {};

template <class T>
struct is_boolean_t : is_same_t<bool, remove_cv_t<T>>::type {};

// Characters
template <typename, typename = void>
struct is_character_t : false_t {};

template <> struct is_character_t<char> : true_t {};
template <> struct is_character_t<signed char> : true_t {};
template <> struct is_character_t<unsigned char> : true_t {};
template <> struct is_character_t<wchar_t> : true_t {};
#if __CAITLYN_HAS_CXX20
template <> struct is_char_t<char8_t> : true_t {};
#endif
template <> struct is_character_t<char16_t> : true_t {};
template <> struct is_character_t<char32_t> : true_t {};

// Integers
template <typename, typename = void>
struct is_integer_t : false_t {};

template <> struct is_integer_t<signed char> : true_t {};
template <> struct is_integer_t<unsigned char> : true_t {};
template <> struct is_integer_t<short> : true_t {};
template <> struct is_integer_t<unsigned short> : true_t {};
template <> struct is_integer_t<int> : true_t {};
template <> struct is_integer_t<unsigned> : true_t {};
template <> struct is_integer_t<long> : true_t {};
template <> struct is_integer_t<unsigned long> : true_t {};
template <> struct is_integer_t<long long> : true_t {};
template <> struct is_integer_t<unsigned long long> : true_t {};

// Floating point
template <typename, typename = void>
struct is_floating_t : false_t {};

template <> struct is_floating_t<float> : true_t {};
template <> struct is_floating_t<double> : true_t {};
template <> struct is_floating_t<long double> : true_t {};

template <class T>
struct is_array_t : false_t {};

template <class T>
struct is_array_t<T[]> : true_t {};

template <class T, std::size_t N>
struct is_array_t<T[N]> : true_t {};

template<class T>
struct is_pointer_t : false_t {};

template<class T>
struct is_pointer_t<T*> : true_t {};

template<class T>
struct is_pointer_t<T* const> : true_t {};

template<class T>
struct is_pointer_t<T* volatile> : true_t {};

template<class T>
struct is_pointer_t<T* const volatile> : true_t {};

template <typename T>
struct is_lvalue_reference_t : false_t {};

template<typename T>
struct is_lvalue_reference_t<T&> : true_t {};

template <typename T>
struct is_rvalue_reference_t : false_t {};

template<typename T>
struct is_rvalue_reference_t<T&&> : true_t {};

__CAITLYN_TRAITS_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif  // CAITLUN_CORE_TRAITS_TYPES_PRIMARY_H_
