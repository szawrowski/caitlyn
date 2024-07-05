// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_
#define CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_

#define __caitlyn__

// Architecture
#if defined(__LP64__) || defined(_LP64) || defined(__x86_64__) || \
    defined(_WIN64)
  #define __caitlyn_x64
#else
  #if defined(__i386__) || defined(_M_IX86) || defined(_WIN32) || \
      defined(__32BIT__)
    #define __caitlyn_x32
    #if defined(__ARM_ARCH_7__) || defined(__arm__) || defined(_M_ARM)
      #define __caitlyn_arm
    #endif
  #else
    #error "Unsupported architecture"
  #endif
#endif

// Operating system
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
  #define __caitlyn_linux
#elif defined(_WIN32)
  #define __caitlyn_windows
#elif defined(__APPLE__)
  #define __caitlyn_apple
#else
  #define __caitlyn_os_unknown
#endif

// Compiler and C++ standard detection
#if defined(__clang__)
  #define __caitlyn_cxxstd __cplusplus
  #define __caitlyn_compiler_clang
#elif defined(__INTEL_COMPILER) || defined(__ICC)
  #define __caitlyn_cxxstd __cplusplus
  #define __caitlyn_compiler_intel
#elif defined(__GNUC__) || defined(__GNUG__)
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

// Additional platform-specific settings
#if defined(__caitlyn_linux)
  #if defined(__WORDSIZE) && (__WORDSIZE == 64)
    #define __caitlyn_wordsize 64
  #else
    #define __caitlyn_wordsize 32
  #endif
#endif


// C++ standard version
#if __caitlyn_cxxstd < 201103L
  #define __caitlyn_cxxstd_ver -1  // legacy
#elif __caitlyn_cxxstd == 201103L
  #define __caitlyn_cxxstd_ver 11
#elif __caitlyn_cxxstd == 201402L
  #define __caitlyn_cxxstd_ver 14
#elif __caitlyn_cxxstd == 201703L
  #define __caitlyn_cxxstd_ver 17
#elif __caitlyn_cxxstd == 202002L
  #define __caitlyn_cxxstd_ver 20
#elif __caitlyn_cxxstd == 202302L
  #define __caitlyn_cxxstd_ver 23
#elif __caitlyn_cxxstd > 202302L
  #define __caitlyn_cxxstd_ver 1  // future
#endif

#endif  // CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_
