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
#include <optional>
#include <regex>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

#include "caitlyn/core/utility/utility.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #include <any>
  #include <optional>
  #include <variant>
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <source_location>
  #include <version>
#endif

#endif  // CAITLYN_CORE_UTILITY_H_
