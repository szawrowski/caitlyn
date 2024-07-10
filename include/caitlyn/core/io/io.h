// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_IO_IO_H_
#define CAITLYN_CORE_IO_IO_H_

#include <cstdio>
#include <iomanip>
#include <ios>
#include <iosfwd>
#include <iostream>

#include "caitlyn/core/io/types/types.h"
#include "caitlyn/core/io/print.h"

#if __caitlyn_has_cxx20
  #include <spanstream>
  #include <syncstream>
#endif

#if __caitlyn_has_cxx23
  #include <print>
#endif

#endif  // CAITLYN_CORE_IO_IO_H_
