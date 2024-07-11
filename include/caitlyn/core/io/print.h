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

#include "caitlyn/core/format/format.h"

namespace cait {

static void print(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << str;
}

template <typename... Args>
static void print(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << fmt(str, std::forward<Args>(args)...);
}

static void println(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << str << get_char(ascii_t::line_feed);
}

template <typename... Args>
static void println(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cout << fmt(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

static void eprint(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << str;
}

template <typename... Args>
static void eprint(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << fmt(str, std::forward<Args>(args)...);
}

static void eprintln(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << str << get_char(ascii_t::line_feed);
}

template <typename... Args>
static void eprintln(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::cerr << fmt(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

static void log(const std::string& str) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::clog << str;
}

template <typename... Args>
static void log(const std::string& str, Args&&... args) {
#if defined(__caitlyn_windows)
  set_windows_utf8_encode();
#endif
  std::ios::sync_with_stdio(false);
  std::clog << fmt(str, std::forward<Args>(args)...)
            << get_char(ascii_t::line_feed);
}

}  // namespace cait

#endif // CAITLYN_CORE_IO_PRINT_H_
