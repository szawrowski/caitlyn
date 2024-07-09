// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_NUMERIC_NUMERIC_H_
#define CAITLYN_CORE_NUMERIC_NUMERIC_H_

#include <cfenv>
#include <cfloat>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdint>
#include <limits>
#include <numeric>
#include <random>
#include <ratio>
#include <valarray>

#include "caitlyn/core/numeric/types/types.h"
#include "caitlyn/core/numeric/utility/utility.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <bit>
  #include <numbers>
#endif

#endif  // CAITLYN_CORE_NUMERIC_NUMERIC_H_
