// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

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
