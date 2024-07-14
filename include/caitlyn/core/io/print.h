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

#include "caitlyn/core/format.h"

namespace cait {

inline void print(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << str;
}

template <typename T>
typename std::enable_if<has_to_string<T>::value>::type print(const T& value) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << value.to_string();
}

template <typename... Args>
void print(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << format(str, std::forward<Args>(args)...);
}

inline void println() {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << get_char(ascii_t::line_feed);
}

inline void println(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << str << get_char(ascii_t::line_feed);
}

template <typename T>
typename std::enable_if<has_to_string<T>::value>::type println(const T& value) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void println(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

inline void eprint(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << str;
}

template <typename T>
typename std::enable_if<has_to_string<T>::value>::type eprint(const T& value) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << value.to_string();
}

template <typename... Args>
void eprint(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << format(str, std::forward<Args>(args)...);
}

inline void eprintln(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << str << get_char(ascii_t::line_feed);
}

template <typename T>
typename std::enable_if<has_to_string<T>::value>::type eprintln(
    const T& value) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void eprintln(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

inline void log(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::clog << str;
}

template <typename T>
typename std::enable_if<has_to_string<T>::value>::type log(const T& value) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::clog << value.to_string() << get_char(ascii_t::line_feed);
}

template <typename... Args>
void log(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::clog << format(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

}  // namespace cait

#endif  // CAITLYN_CORE_IO_PRINT_H_
