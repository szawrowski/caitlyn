// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_IO_DEFINITIONS_H_
#define CAITLYN_CORE_IO_IO_DEFINITIONS_H_

#include <fstream>
#include <streambuf>

#include "caitlyn/core/defs/basic_types.h"

#if defined(__caitlyn_windows)
  #include <windows.h>
#endif

BEGIN_CAITLYN_NS

template <typename CharT>
using std_basic_istream = std::basic_istream<CharT>;
using istream_t = std_basic_istream<u8char_t>;
using xistream_t = std_basic_istream<xchar_t>;

template <typename CharT>
using std_basic_ostream = std::basic_ostream<CharT>;
using ostream_t = std_basic_ostream<u8char_t>;
using xostream_t = std_basic_ostream<xchar_t>;

template <typename CharT>
using std_basic_iostream = std::basic_iostream<CharT>;
using iostream_t = std_basic_iostream<u8char_t>;
using xiostream_t = std_basic_iostream<xchar_t>;

template <typename CharT>
using std_basic_streambuf = std::basic_streambuf<CharT>;
using streambuf_t = std_basic_streambuf<u8char_t>;
using xstreambuf_t = std_basic_streambuf<xchar_t>;

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#endif

END_CAITLYN_NS

#endif // CAITLYN_CORE_IO_IO_DEFINITIONS_H_
