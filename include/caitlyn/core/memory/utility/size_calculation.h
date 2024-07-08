// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_UTILITY_SIZE_CALCULATION_H_
#define CAITLYN_CORE_MEMORY_UTILITY_SIZE_CALCULATION_H_

#include "caitlyn/core/memory/types/memory_types.h"

__caitlyn_begin_global_namespace

template <typename T>
static constexpr size_t size_of(const memfmt_t mf = memfmt_t::byte) {
  return mf == memfmt_t::byte ? sizeof(T) : sizeof(T) * 8;
}

template <typename T>
static constexpr size_t size_of(const T& value,
                                const memfmt_t mf = memfmt_t::byte) {
  return mf == memfmt_t::byte ? sizeof(value) : sizeof(value) * 8;
}

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_MEMORY_UTILITY_SIZE_CALCULATION_H_
