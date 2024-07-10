// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_H_
#define CAITLYN_CORE_IO_TYPES_FILE_H_

#include <fstream>

#include "caitlyn/core/core.h"

__caitlyn_begin_global_namespace

using ifstream_t = std::basic_ifstream<char_t>;
using ofstream_t = std::basic_ofstream<char_t>;
using fstream_t = std::basic_fstream<char_t>;
using filebuf_t = std::basic_filebuf<char_t>;

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_IO_TYPES_FILE_H_
