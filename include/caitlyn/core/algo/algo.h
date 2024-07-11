// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ALGO_ALGO_H_
#define CAITLYN_CORE_ALGO_ALGO_H_

#include <algorithm>

#include "caitlyn/__detail.h"

#if __caitlyn_has_cxx17
  #include <execution>
#endif

#if __caitlyn_has_cxx20
  #include <ranges>
#endif

#if __caitlyn_has_cxx23
  #include <generator>
#endif

#endif  // CAITLYN_CORE_ALGO_ALGO_H_
