// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_FILE_H_
#define CAITLYN_CORE_IO_TYPES_FILE_H_

#include "caitlyn/core/io/types/file_reader.h"
#include "caitlyn/core/io/types/file_writer.h"

namespace cait {

using ifile = file_reader<char_t>;
using ofile = file_writer<char_t>;

}  // namespace cait

#endif  // CAITLYN_CORE_IO_TYPES_FILE_H_
