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
  #define __caitlyn_arch 64
#else
  #if defined(__i386__) || defined(_M_IX86) || defined(_WIN32) || \
      defined(__32BIT__)
    #define __caitlyn_arch 32
  #elif defined(__ARM_ARCH_7__) || defined(__arm__) || defined(_M_ARM)
    #define __caitlyn_arch 32
    #define __caitlyn_arm
  #else
    #error "Unsupported architecture"
  #endif
#endif

// Operating system
#if defined(__linux) || defined(__linux__) || defined(__gnu_linux__)
  #define __caitlyn_linux
  #define __caitlyn_unix
#elif defined(__APPLE__)
  #define __caitlyn_apple
  #define __caitlyn_unix
#elif defined(_WIN32)
  #define __caitlyn_windows
#else
  #define __caitlyn_os_unknown
#endif

// Compiler detection
#if defined(__clang__)
  #define __caitlyn_compiler_clang
#elif defined(__INTEL_COMPILER) || defined(__ICC)
  #define __caitlyn_compiler_intel
#elif defined(__GNUC__) || defined(__GNUG__)
  #define __caitlyn_compiler_gcc
#elif defined(_MSC_VER)
  #define __caitlyn_compiler_msvc
#else
  #define __caitlyn_compiler_unknown
#endif

// C++ standard detection
#if defined(__caitlyn_unix)
  #define __caitlyn_cxxstd __cplusplus
#elif defined(__caitlyn_windows)
  #if defined(__caitlyn_compiler_msvc)
    #define __caitlyn_cxxstd _MSVC_LANG
  #else
    #define __caitlyn_cxxstd __cplusplus
  #endif
#else
  #error "C++ standard macro undefined"
#endif

#if defined(__caitlyn_cxxstd)
  #define __caitlyn_cxxstd_legacy_ver = 199711L
  #define __caitlyn_cxxstd11_ver = 201103L
  #define __caitlyn_cxxstd14_ver = 201402L
  #define __caitlyn_cxxstd17_ver = 201703L
  #define __caitlyn_cxxstd20_ver = 202002L
  #define __caitlyn_cxxstd23_ver = 202302L
#endif

// Additional platform-specific settings
#if defined(__caitlyn_linux)
  #if defined(__WORDSIZE) && (__WORDSIZE == 64)
    #define __caitlyn_wordsize 64
  #else
    #define __caitlyn_wordsize 32
  #endif
#endif

#endif  // CAITLYN_CORE_DEFS_CORE_DEFINITIONS_H_
