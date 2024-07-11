// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_H_
#define CAITLYN_CORE_IO_TYPES_FILE_H_

#include "caitlyn/core/unicode/types/unicode_file_reader.h"
#include "caitlyn/core/unicode/types/unicode_file_writer.h"

namespace cait {

using ifstream_t = std::basic_ifstream<char_t>;
using ofstream_t = std::basic_ofstream<char_t>;
using fstream_t = std::basic_fstream<char_t>;
using filebuf_t = std::basic_filebuf<char_t>;

using ifile = unicode_file_reader<u8char_t>;
using ofile = unicode_file_writer<u8char_t>;

}  // namespace cait

#endif  // CAITLYN_CORE_IO_TYPES_FILE_H_
