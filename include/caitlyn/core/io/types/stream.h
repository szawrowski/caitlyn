// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_STREAM_H_
#define CAITLYN_CORE_IO_TYPES_STREAM_H_

#include <streambuf>

#include "caitlyn/__detail.h"

#if defined(__caitlyn_windows)
  #define NOMINMAX
  #include <windows.h>
#endif

namespace cait {

using istream_t = std::basic_istream<char_t>;
using ostream_t = std::basic_ostream<char_t>;
using iostream_t = std::basic_iostream<char_t>;
using streambuf_t = std::basic_streambuf<char_t>;

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#endif

}  // namespace cait

#endif  // CAITLYN_CORE_IO_TYPES_STREAM_H_
