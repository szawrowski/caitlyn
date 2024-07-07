// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_IO_DEFINITIONS_H_
#define CAITLYN_CORE_IO_IO_DEFINITIONS_H_

#include <streambuf>

#include "caitlyn/core/defs/basic_types.h"

#if defined(__caitlyn_windows)
  #include <windows.h>
#endif

BEGIN_CAITLYN_NS

template <typename CharT>
using basic_istream_t = std::basic_istream<CharT>;
using istream_t = basic_istream_t<u8char_t>;
using xistream_t = basic_istream_t<xchar_t>;

template <typename CharT>
using basic_ostream_t = std::basic_ostream<CharT>;
using ostream_t = basic_ostream_t<u8char_t>;
using xostream_t = basic_ostream_t<xchar_t>;

template <typename CharT>
using basic_iostream_t = std::basic_iostream<CharT>;
using iostream_t = basic_iostream_t<u8char_t>;
using xiostream_t = basic_iostream_t<xchar_t>;

template <typename CharT>
using basic_streambuf_t = std::basic_streambuf<CharT>;
using streambuf_t = basic_streambuf_t<u8char_t>;
using xstreambuf_t = basic_streambuf_t<xchar_t>;

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#endif

END_CAITLYN_NS

#endif // CAITLYN_CORE_IO_IO_DEFINITIONS_H_
