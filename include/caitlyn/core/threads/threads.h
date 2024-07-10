// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_THREADS_THREADS_H_
#define CAITLYN_CORE_THREADS_THREADS_H_

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#include "caitlyn/__detail.h"

#if __caitlyn_has_cxx14
  #include <shared_mutex>
#endif

#if __caitlyn_has_cxx20
  #include <barrier>
  #include <coroutine>
  #include <latch>
  #include <semaphore>
  #include <stop_token>
#endif

#endif  // CAITLYN_CORE_THREADS_THREADS_H_
