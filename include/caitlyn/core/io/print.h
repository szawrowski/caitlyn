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

#ifndef CAITLYN_CORE_IO_PRINT_H_
#define CAITLYN_CORE_IO_PRINT_H_

#include <iostream>

#include "caitlyn/core/string.h"
#include "caitlyn/core/traits.h"

namespace cait {

inline void print(const string_t& str) {
  std::ios::sync_with_stdio(false);
  std::cout << str;
}

template <typename T>
required_t<has_to_string<T>()> print(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.to_string();
}

template <typename T>
required_t<has_str<T>()> print(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.str();
}

template <typename T>
required_t<has_std_string<T>()> print(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.std_string();
}

template <typename... Args>
void print(const string_t& str, Args&&... args) {
  std::ios::sync_with_stdio(false);
  std::cout << format(str, std::forward<Args>(args)...);
}

inline void println() {
  std::ios::sync_with_stdio(false);
  std::cout << get_char(ascii_t::line_feed);
}

inline void println(const string_t& str) {
  std::ios::sync_with_stdio(false);
  std::cout << str << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_to_string<T>()> println(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_str<T>()> println(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.str() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_std_string<T>()> println(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cout << value.std_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void println(const string_t& str, Args&&... args) {
  std::ios::sync_with_stdio(false);
  std::cout << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

inline void eprint(const string_t& str) {
  std::ios::sync_with_stdio(false);
  std::cerr << str;
}

template <typename T>
required_t<has_to_string<T>()> eprint(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.to_string();
}

template <typename T>
required_t<has_str<T>()> eprint(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.str();
}

template <typename T>
required_t<has_std_string<T>()> eprint(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.std_string();
}

template <typename... Args>
void eprint(const string_t& str, Args&&... args) {
  std::ios::sync_with_stdio(false);
  std::cerr << format(str, std::forward<Args>(args)...);
}

inline void eprintln(const string_t& str) {
  std::ios::sync_with_stdio(false);
  std::cerr << str << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_to_string<T>()> eprintln(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_str<T>()> eprintln(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.str() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_std_string<T>()> eprintln(const T& value) {
  std::ios::sync_with_stdio(false);
  std::cerr << value.std_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void eprintln(const string_t& str, Args&&... args) {
  std::ios::sync_with_stdio(false);
  std::cerr << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

inline void log(const string_t& str) {
  std::ios::sync_with_stdio(false);
  std::clog << str;
}

template <typename T>
required_t<has_to_string<T>()> log(const T& value) {
  std::ios::sync_with_stdio(false);
  std::clog << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_str<T>()> log(const T& value) {
  std::ios::sync_with_stdio(false);
  std::clog << value.str() << get_char(ascii_t::line_feed);
}

template <typename T>
required_t<has_std_string<T>()> log(const T& value) {
  std::ios::sync_with_stdio(false);
  std::clog << value.std_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void log(const string_t& str, Args&&... args) {
  std::ios::sync_with_stdio(false);
  std::clog << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

}  // namespace cait

#endif  // CAITLYN_CORE_IO_PRINT_H_
