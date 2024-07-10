// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_
#define CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_

#include <stdexcept>

#include "caitlyn/core/format/defs/defs.h"

__caitlyn_begin_global_namespace
__caitlyn_begin_format_namespace

class format_error_t final : public std::runtime_error {
public:
  explicit format_error_t(const std::string& message)
      : std::runtime_error(message) {}
};

__caitlyn_end_format_namespace
__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_FORMAT_TYPES_FORMAT_ERROR_H_
