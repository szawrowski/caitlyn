// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_UTILITY_H_
#define CAITLYN_CORE_UTILITY_UTILITY_H_

#include <bitset>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <regex>
#include <type_traits>
#include <typeindex>
#include <typeinfo>

#include "caitlyn/core/utility/comparators/comparators.h"
#include "caitlyn/core/utility/random/random.h"
#include "caitlyn/core/utility/types/types.h"

#if __caitlyn_has_cxx17
  #include <any>
#endif
#if __caitlyn_has_cxx20
  #include <source_location>
  #include <version>
#endif

#endif  // CAITLYN_CORE_UTILITY_UTILITY_H_
