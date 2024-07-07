// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_THREADS_H_
#define CAITLYN_CORE_THREADS_H_

#include <condition_variable>
#include <future>
#include <mutex>
#include <thread>

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd14_ver)
  #include <shared_mutex>
#endif

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #include <barrier>
  #include <coroutine>
  #include <latch>
  #include <semaphore>
  #include <stop_token>
#endif

#endif  // CAITLYN_CORE_THREADS_H_
