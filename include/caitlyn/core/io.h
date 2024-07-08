// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_H_
#define CAITLYN_CORE_IO_H_

#include <cstdio>
#include <iomanip>
#include <ios>
#include <iosfwd>

#include "caitlyn/core/io/io.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <spanstream>
  #include <syncstream>
#endif

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd23_ver)
  #include <print>
#endif

#endif  // CAITLYN_CORE_IO_H_
