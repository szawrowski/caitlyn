// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_TYPES_STREAM_H_
#define CAITLYN_CORE_IO_TYPES_STREAM_H_

#include <iostream>
#include <streambuf>

#include "caitlyn/base.h"

#if defined(__caitlyn_windows)
  #define NOMINMAX
  #include <windows.h>
#endif

namespace cait {

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#endif

}  // namespace cait

#endif  // CAITLYN_CORE_IO_TYPES_STREAM_H_
