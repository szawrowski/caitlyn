// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_
#define CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_

#define __caitlyn__

// Operating system
#if defined(__linux__)
  #define __caitlyn_os_linux
  #if !defined(__x86_64__)
    #define __caitlyn_arch32
  #else
    #define __caitlyn_arch64
  #endif
#elif defined(__APPLE__)
  #define __caitlyn_os_osx
  #if !defined(__x86_64__)
    #define __caitlyn_arch32
  #else
    #define __caitlyn_arch64
  #endif
#elif defined(_WIN32)
  #define __caitlyn_os_windows
  #if !defined(_WIN64)
    #define __caitlyn_arch32
  #else
    #define __caitlyn_arch64
  #endif
#else
  #define __caitlyn_os_unknown
#endif

// Compiler
#if defined(__clang__)
  #define __caitlyn_cxxstd __cplusplus
  #define __caitlyn_compiler_clang
#elif defined(__GNUC__)
  #define __caitlyn_cxxstd __cplusplus
  #define __caitlyn_compiler_gcc
#elif defined(_MSC_VER)
  #define __caitlyn_cxxstd _MSVC_LANG
  #define __caitlyn_compiler_msvc
#else
  #if defined(__cplusplus)
    #define __caitlyn_cxxstd __cplusplus
  #endif
  #define __caitlyn_compiler_unknown
#endif

// Standard
#if __caitlyn_cxxstd < 201103L
  #define __caitlyn_cxxstd_legacy
#elif __caitlyn_cxxstd == 201103L
  #define __caitlyn_cxxstd11
#elif __caitlyn_cxxstd == 201402L
  #define __caitlyn_cxxstd14
#elif __caitlyn_cxxstd == 201703L
  #define __caitlyn_cxxstd17
#elif __caitlyn_cxxstd == 202002L
  #define __caitlyn_cxxstd20
#elif __caitlyn_cxxstd == 202302L
  #define __caitlyn_cxxstd23
#elif __caitlyn_cxxstd > 202302L
  #define __caitlyn_cxxstd_future
#endif

#endif  // CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_
