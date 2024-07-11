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

#include "caitlyn/core/math.h"
#include "caitlyn/core/numeric/types/types.h"
#include "caitlyn/core/numeric/utility/utility.h"

#if __caitlyn_has_cxx20
  #include <bit>
  #include <numbers>
#endif

#if __caitlyn_has_cxx23
  #include <stdfloat>
#endif

#endif  // CAITLYN_CORE_NUMERIC_NUMERIC_H_
