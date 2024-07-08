// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UTILITY_H_
#define CAITLYN_CORE_UTILITY_H_

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

#include "caitlyn/core/utility/utility.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #include <any>
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <source_location>
  #include <version>
#endif

#endif  // CAITLYN_CORE_UTILITY_H_
