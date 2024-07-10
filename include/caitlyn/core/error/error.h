// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ERROR_ERROR_H_
#define CAITLYN_CORE_ERROR_ERROR_H_

#include <cassert>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <system_error>

#include "caitlyn/core/error/types/types.h"

#if __caitlyn_has_cxx20
  #include <stacktrace>
#endif

#if __caitlyn_has_cxx23
  #include <expected>
#endif

#endif  // CAITLYN_CORE_ERROR_ERROR_H_
