// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_CHAR_CHAR_H_
#define CAITLYN_CORE_CHAR_CHAR_H_

#include <cctype>
#include <cwchar>
#include <cwctype>
#include <cuchar>

#include "caitlyn/core/char/types/types.h"
#include "caitlyn/core/char/utility/utility.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #include <charconv>
#endif

#endif // CAITLYN_CORE_CHAR_CHAR_H_
