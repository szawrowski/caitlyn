// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_H_
#define CAITLYN_CORE_STRING_H_

#include <cctype>
#include <cstring>
#include <cwchar>
#include <cwctype>
#include <cuchar>

#include "caitlyn/core/char/char.h"
#include "caitlyn/core/string/string.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #include <charconv>
#endif

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <format>
#endif

#endif  // CAITLYN_CORE_STRING_H_
