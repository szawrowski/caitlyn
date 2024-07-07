// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ALGO_H_
#define CAITLYN_CORE_ALGO_H_

#include <algorithm>

#include "caitlyn/core/defs/core_definitions.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #include <execution>
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <ranges>
#endif

#endif  // CAITLYN_CORE_ALGO_H_
