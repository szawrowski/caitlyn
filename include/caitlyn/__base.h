/**
 * This file is part of the Caitlyn library
 * Copyright (C) 2024 Alexander Szawrowski
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#ifndef CAITLYN_BASE_H_
#define CAITLYN_BASE_H_

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
#elif defined(__APPLE__)
  #define __caitlyn_apple
#elif defined(_WIN32)
  #define __caitlyn_windows
#else
  #define __caitlyn_os_unknown
#endif

#if defined(__caitlyn_linux) || defined(__caitlyn_apple)
  #define __caitlyn_unix
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
#endif

// Additional platform-specific settings
#if defined(__caitlyn_linux)
  #if defined(__WORDSIZE) && (__WORDSIZE == 64)
    #define __caitlyn_wordsize 64
  #else
    #define __caitlyn_wordsize 32
  #endif
#endif

#if (__caitlyn_cxxstd >= 199711L)
  #define __caitlyn_has_cxx98 1
#else
  #define __caitlyn_has_cxx98 0
#endif
#if (__caitlyn_cxxstd >= 199711L)
  #define __caitlyn_has_cxx11 1
#else
  #define __caitlyn_has_cxx11 0
#endif
#if (__caitlyn_cxxstd >= 201402L)
  #define __caitlyn_has_cxx14 1
#else
  #define __caitlyn_has_cxx14 0
#endif
#if (__caitlyn_cxxstd >= 201703L)
  #define __caitlyn_has_cxx17 1
#else
  #define __caitlyn_has_cxx17 0
#endif
#if (__caitlyn_cxxstd >= 202002L)
  #define __caitlyn_has_cxx20 1
#else
  #define __caitlyn_has_cxx20 0
#endif
#if (__caitlyn_cxxstd >= 202302L)
  #define __caitlyn_has_cxx23 1
#else
  #define __caitlyn_has_cxx23 0
#endif

#if __caitlyn_has_cxx11
  #define __caitlyn_constexpr11 constexpr
#else
  #define __caitlyn_constexpr11
#endif
#if __caitlyn_has_cxx14
  #define __caitlyn_constexpr14 constexpr
#else
  #define __caitlyn_constexpr14
#endif
#if __caitlyn_has_cxx17
  #define __caitlyn_constexpr17 constexpr
#else
  #define __caitlyn_constexpr17
#endif
#if __caitlyn_has_cxx20
  #define __caitlyn_constexpr20 constexpr
#else
  #define __caitlyn_constexpr20
#endif
#if __caitlyn_has_cxx23
  #define __caitlyn_constexpr23 constexpr
#else
  #define __caitlyn_constexpr23
#endif

#if __caitlyn_has_cxx17
  #define __caitlyn_nodiscard [[nodiscard]]
#else
  #define __caitlyn_nodiscard
#endif

#include <cstddef>
#include <cstdint>

namespace cait {

// Common haracters
using uchar_t = unsigned char;
using schar_t = signed char;

// Unicode characters
#if __caitlyn_has_cxx20
using u8char_t = char8_t;
#else
using u8char_t = char;
#endif
using u16char_t = char16_t;
using u32char_t = char32_t;

// Special integrals
using sbyte_t = schar_t;
using byte_t = uchar_t;
using ssize_t = ptrdiff_t;

// Floating point
using float32_t = float;
using float64_t = double;
using floatx_t = long double;

}  // namespace cait

#if defined(__caitlyn_windows)
  #define NOMINMAX
  #include <windows.h>
#endif

namespace cait {

#if defined(__caitlyn_windows)
inline void set_windows_utf8_encode() {
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
}
#else
inline void set_windows_utf8_encode() {}
#endif

}  // namespace cait

#endif  // CAITLYN_BASE_H_
