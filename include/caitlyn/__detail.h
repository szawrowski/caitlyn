// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_DETAIL_H_
#define CAITLYN_DETAIL_H_

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
using u8char_t = char_t;
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

inline cait::char_t operator""_c(const char val) {
  return val;
}

inline cait::uchar_t operator""_uc(const unsigned long long val) {
  return static_cast<cait::uchar_t>(val);
}

inline cait::schar_t operator""_sc(const unsigned long long val) {
  return static_cast<cait::schar_t>(val);
}

inline cait::xchar_t operator""_xc(const wchar_t val) {
  return static_cast<cait::xchar_t>(val);
}

inline cait::u8char_t operator""_c8(const unsigned long long val) {
  return static_cast<cait::u8char_t>(val);
}

inline cait::u16char_t operator""_c16(const unsigned long long val) {
  return static_cast<cait::u16char_t>(val);
}

inline cait::u32char_t operator""_c32(const unsigned long long val) {
  return static_cast<cait::u32char_t>(val);
}

inline cait::sbyte_t operator""_sbyte(const unsigned long long val) {
  return static_cast<cait::sbyte_t>(val);
}

inline cait::byte_t operator""_byte(const unsigned long long val) {
  return static_cast<cait::byte_t>(val);
}

inline cait::int_t operator""_int(const unsigned long long val) {
  return static_cast<cait::int_t>(val);
}

inline cait::uint_t operator""_uint(const unsigned long long val) {
  return static_cast<cait::uint_t>(val);
}

inline cait::int8_t operator""_i8(const unsigned long long val) {
  return static_cast<cait::int8_t>(val);
}

inline cait::uint8_t operator""_u8(const unsigned long long val) {
  return static_cast<cait::uint8_t>(val);
}

inline cait::int16_t operator""_i16(const unsigned long long val) {
  return static_cast<cait::int16_t>(val);
}

inline cait::uint16_t operator""_u16(const unsigned long long val) {
  return static_cast<cait::uint16_t>(val);
}

inline cait::int32_t operator""_i32(const unsigned long long val) {
  return static_cast<cait::int32_t>(val);
}

inline cait::uint32_t operator""_u32(const unsigned long long val) {
  return static_cast<cait::uint32_t>(val);
}

inline cait::int64_t operator""_i64(const unsigned long long val) {
  return static_cast<cait::int64_t>(val);
}

inline cait::uint64_t operator""_u64(const unsigned long long val) {
  return static_cast<cait::uint64_t>(val);
}

inline cait::ssize_t operator""_sz(const unsigned long long val) {
  return static_cast<cait::ssize_t>(val);
}

inline cait::size_t operator""_ssz(const unsigned long long val) {
  return static_cast<cait::size_t>(val);
}

inline cait::float32_t operator""_f32(const long double val) {
  return static_cast<cait::float32_t>(val);
}

inline cait::float64_t operator""_f64(const long double val) {
  return static_cast<cait::float64_t>(val);
}

inline cait::floatx_t operator""_fx(const long double val) {
  return val;
}

#endif  // CAITLYN_DETAIL_H_
