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

// C++ standard versions
#if defined(__caitlyn_cxxstd)
  #define __caitlyn_cxxstd98_ver 199711L
  #define __caitlyn_cxxstd11_ver 201103L
  #define __caitlyn_cxxstd14_ver 201402L
  #define __caitlyn_cxxstd17_ver 201703L
  #define __caitlyn_cxxstd20_ver 202002L
  #define __caitlyn_cxxstd23_ver 202302L
#endif

// Additional platform-specific settings
#if defined(__caitlyn_linux)
  #if defined(__WORDSIZE) && (__WORDSIZE == 64)
    #define __caitlyn_wordsize 64
  #else
    #define __caitlyn_wordsize 32
  #endif
#endif

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd98_ver)
  #define __caitlyn_has_cxx98 1
#else
  #define __caitlyn_has_cxx98 0
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd11_ver)
  #define __caitlyn_has_cxx11 1
#else
  #define __caitlyn_has_cxx11 0
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd14_ver)
  #define __caitlyn_has_cxx14 1
#else
  #define __caitlyn_has_cxx14 0
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  #define __caitlyn_has_cxx17 1
#else
  #define __caitlyn_has_cxx17 0
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd20_ver)
  #define __caitlyn_has_cxx20 1
#else
  #define __caitlyn_has_cxx20 0
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd23_ver)
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

namespace cait {

// Common haracters
using char_t = char;
using uchar_t = unsigned char;
using schar_t = signed char;
using xchar_t = wchar_t;

// Unicode characters
#if __caitlyn_has_cxx20
using u8char_t = char8_t;
#else
using u8char_t = char_t;
#endif
using u16char_t = char16_t;
using u32char_t = char32_t;

// Special integrals
using sbyte_t = schar_t;
using byte_t = uchar_t;
using int_t = decltype(0);
using uint_t = decltype(0U);
// Common integrals
using int8_t = schar_t;
using uint8_t = uchar_t;
using int16_t = signed short int;
using uint16_t = unsigned short int;
using int32_t = int_t;
using uint32_t = uint_t;
#if defined(__caitlyn_unix) && (__caitlyn_arch == 64)
using int64_t = decltype(0L);
using uint64_t = decltype(0UL);
#else
using int64_t = decltype(0LL);
using uint64_t = decltype(0ULL);
#endif
// System integrals
using ptrdiff_t =
    decltype(static_cast<int_t*>(nullptr) - static_cast<int_t*>(nullptr));
using ssize_t = ptrdiff_t;
using size_t = decltype(sizeof(0));
using uintmax_t = size_t;
using uintptr_t = size_t;
using streamsize_t = ptrdiff_t;

// Floating point
using float32_t = decltype(0.0f);
using float64_t = decltype(0.0);
using floatx_t = decltype(0.0L);

// Logical
using bool_t = decltype(true);

// System
using null_t = decltype(nullptr);

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
#endif

}  // namespace cait

#endif  // CAITLYN_BASE_H_
