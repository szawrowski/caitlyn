// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_MEMORY_H_
#define CAITLYN_CORE_MEMORY_MEMORY_H_

#include <memory>
#include <new>
#include <scoped_allocator>

#include "caitlyn/core/memory/pointers/pointers.h"
#include "caitlyn/core/memory/types/types.h"
#include "caitlyn/core/memory/utility/utility.h"

#if (__caitlyn_cxxstd > __caitlyn_cxxstd14_ver)
  #include <memory_resource>
#endif

#endif  // CAITLYN_CORE_MEMORY_MEMORY_H_
