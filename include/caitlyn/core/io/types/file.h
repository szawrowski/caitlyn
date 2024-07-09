// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_H_
#define CAITLYN_CORE_IO_TYPES_FILE_H_

#include <fstream>

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

template <typename CharT>
using basic_ifstream_t = std::basic_ifstream<CharT>;
using ifstream_t = basic_ifstream_t<u8char_t>;
using xifstream_t = basic_ifstream_t<xchar_t>;

template <typename CharT>
using basic_ofstream_t = std::basic_ofstream<CharT>;
using ofstream_t = basic_ofstream_t<u8char_t>;
using xofstream_t = basic_ofstream_t<xchar_t>;

template <typename CharT>
using basic_fstream_t = std::basic_fstream<CharT>;
using fstream_t = basic_fstream_t<u8char_t>;
using xfstream_t = basic_fstream_t<xchar_t>;

template <typename CharT>
using basic_filebuf = std::basic_filebuf<CharT>;
using filebuf_t = basic_filebuf<u8char_t>;
using xfilebuf_t = basic_filebuf<xchar_t>;

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_IO_TYPES_FILE_H_
