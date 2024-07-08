// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ERROR_H_
#define CAITLYN_CORE_ERROR_H_

#include <cassert>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <system_error>

#include "caitlyn/core/core.h"
#include "caitlyn/core/error/error.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <stacktrace>
#endif

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd23_ver)
  #include <expected>
#endif

#endif  // CAITLYN_CORE_ERROR_H_
