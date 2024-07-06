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

using streambuf_t = std::basic_streambuf<u8char_t>;
using xstreambuf_t = std::basic_streambuf<xchar_t>;

using istream_t = std::basic_istream<u8char_t>;
using xistream_t = std::basic_istream<xchar_t>;

using ostream_t = std::basic_ostream<u8char_t>;
using xostream_t = std::basic_ostream<xchar_t>;

using iostream_t = std::basic_iostream<u8char_t>;
using xiostream_t = std::basic_iostream<xchar_t>;

using ifile_t = std::basic_ifstream<u8char_t>;
using xifile_t = std::basic_ifstream<xchar_t>;

using ofile_t = std::basic_ofstream<u8char_t>;
using xofile_t = std::basic_ofstream<xchar_t>;

using file_t = std::basic_fstream<u8char_t>;
using xfile_t = std::basic_fstream<xchar_t>;

using filebuf_t = std::basic_filebuf<u8char_t>;
using xfilebuf_t = std::basic_filebuf<xchar_t>;

#define std_input std::in
#define std_output std::cout

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#endif

END_CAITLYN_NS

#endif // CAITLYN_CORE_IO_IO_DEFINITIONS_H_
