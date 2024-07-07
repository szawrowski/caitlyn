// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_FILE_DEFINITIONS_H_
#define CAITLYN_CORE_IO_FILE_DEFINITIONS_H_

#include <fstream>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename CharT>
using basic_ifile_t = std::basic_ifstream<CharT>;
using ifile_t = basic_ifile_t<u8char_t>;
using xifile_t = basic_ifile_t<xchar_t>;

template <typename CharT>
using basic_ofile_t = std::basic_ofstream<CharT>;
using ofile_t = basic_ofile_t<u8char_t>;
using xofile_t = basic_ofile_t<xchar_t>;

template <typename CharT>
using basic_file_t = std::basic_fstream<CharT>;
using file_t = basic_file_t<u8char_t>;
using xfile_t = basic_file_t<xchar_t>;

template <typename CharT>
using basic_filebuf = std::basic_filebuf<CharT>;
using filebuf_t = basic_filebuf<u8char_t>;
using xfilebuf_t = basic_filebuf<xchar_t>;

END_CAITLYN_NS

static cait::file_t operator""_file(const cait::u8char_t* symbol,
                                    const std::size_t) {
  return cait::file_t{symbol};
}

#endif  // CAITLYN_CORE_IO_FILE_DEFINITIONS_H_
