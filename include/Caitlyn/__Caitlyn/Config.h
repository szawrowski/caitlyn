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

#ifndef CAITLYN_CONFIG_H_
#define CAITLYN_CONFIG_H_

#define __CAITLYN__

#define __CAITLYN_MAJOR_VERSION__ 1
#define __CAITLYN_MINOR_VERSION__ 0
#define __CAITLYN_PATCH_VERSION__ 0

#define __CAITLYN_STRINGIFY(...) #__VA_ARGS__
#define __CAITLYN_TOSTRING(x) __CAITLYN_STRINGIFY(x)

#define __CAITLYN_VERSION                                                                                              \
    "Caitlyn " __CAITLYN_TOSTRING(__CAITLYN_MAJOR_VERSION__) "." __CAITLYN_TOSTRING(                                   \
        __CAITLYN_MINOR_VERSION__) "." __CAITLYN_TOSTRING(__CAITLYN_MINOR_VERSION__)

//Architecture
#if defined(__i386__) || defined(_M_IX86) || defined(__32BIT__)
    #define __CAITLYN_ARCH_X86
    #define __CAITLYN_ARCH 32
#elif defined(__LP64__) || defined(_LP64) || defined(__x86_64__) || defined(_M_X64)
    #define __CAITLYN_ARCH_X86_64
    #define __CAITLYN_ARCH 64
#elif defined(__arm__) || defined(__ARM_ARCH_7__) || defined(__thumb__) || defined(_M_ARM)
    #define __CAITLYN_ARCH_ARM
    #define __CAITLYN_ARCH 32
#elif defined(__aarch64__) || defined(_M_ARM64)
    #define __CAITLYN_ARCH_ARM64
    #define __CAITLYN_ARCH 64
#else
    #error "Unsupported Architecture"
#endif

//Operating System
#if defined(__linux__) || defined(__linux) || defined(__gnu_linux__)
    #define __CAITLYN_OS_LINUX
    #define __CAITLYN_OS_NAME "Linux"
#elif defined(__APPLE__) && defined(__MACH__)
    #define __CAITLYN_OS_APPLE
    #define __CAITLYN_OS_NAME "Apple"
#elif defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined(_WIN64)
    #define __CAITLYN_OS_WINDOWS
    #define __CAITLYN_OS_NAME "Windows"
#elif defined(__ANDROID__)
    #define __CAITLYN_OS_ANDROID
    #define __CAITLYN_OS_NAME "Android"
#else
    #error "Unsupported Operating System"
#endif

#if defined(__CAITLYN_OS_LINUX) || defined(__CAITLYN_OS_APPLE)
    #define __CAITLYN_OS_UNIX
#endif

//Additional Platform-specific Settings
#ifdef __CAITLYN_OS_UNIX
    #if (__CAITLYN_ARCH == 64) && !defined(__ILP32__)
        #define __CAITLYN_WORDSIZE 64
    #else
        #define __CAITLYN_WORDSIZE 32
    #endif
#endif

//Compiler
#if defined(__clang__)
    #define __CAITLYN_COMPILER_CLANG
#elif defined(__GNUC__) || defined(__GNUG__)
    #define __CAITLYN_COMPILER_GCC
    #if defined(__MINGW32__) || defined(__MINGW64__)
        #define __CAITLYN_COMPILER_MINGW
    #endif
#elif defined(_MSC_VER)
    #define __CAITLYN_COMPILER_MSVC
#elif defined(__INTEL_COMPILER) || defined(__ICC)
    #define __CAITLYN_COMPILER_INTEL
#else
    #error "Unknown Compiler"
#endif

#if defined(__CAITLYN_COMPILER_CLANG)
    #define __CAITLYN_COMPILER_VERSION                                                                                 \
        "Clang " __CAITLYN_TOSTRING(__clang_major__) "." __CAITLYN_TOSTRING(__clang_minor__)
#elif defined(__CAITLYN_COMPILER_GCC)
    #if defined(__CAITLYN_COMPILER_MINGW)
        #define __CAITLYN_COMPILER_VERSION "MinGW " __CAITLYN_TOSTRING(__GNUC__) "." __CAITLYN_TOSTRING(__GNUC_MINOR__)
    #else
        #define __CAITLYN_COMPILER_VERSION "GCC " __CAITLYN_TOSTRING(__GNUC__) "." __CAITLYN_TOSTRING(__GNUC_MINOR__)
    #endif
#elif defined(__CAITLYN_COMPILER_MSVC)
    #define __CAITLYN_COMPILER_VERSION "MSVC " __CAITLYN_TOSTRING(_MSC_VER)
#elif defined(__CAITLYN_COMPILER_INTEL)
    #define CAITLYN_COMPILER_VERSION "Intel " __CAITLYN_TOSTRING(__INTEL_COMPILER)
#endif

//Standard
#if defined(__cplusplus)
    #if defined(__CAITLYN_COMPILER_MSVC)
        #define __CAITLYN_CXX_STANDARD _MSVC_LANG
    #else
        #define __CAITLYN_CXX_STANDARD __cplusplus
    #endif
#else
    #error "Undefined __cplusplus"
#endif

#define __CAITLYN_CXX_STANDARD98_VERSION 199711L
#define __CAITLYN_CXX_STANDARD11_VERSION 201103L
#define __CAITLYN_CXX_STANDARD14_VERSION 201402L
#define __CAITLYN_CXX_STANDARD17_VERSION 201703L
#define __CAITLYN_CXX_STANDARD20_VERSION 202002L
#define __CAITLYN_CXX_STANDARD23_VERSION 202300L

#if __CAITLYN_CXX_STANDARD >= __CAITLYN_CXX_STANDARD11_VERSION
    #define __CAITLYN_HAS_CXX11 1
    #define __CAITLYN_CONSTEXPR11 constexpr
    #define __CAITLYN_NOEXCEPT11 noexcept
#else
    #define __CAITLYN_HAS_CXX11 0
    #define __CAITLYN_CONSTEXPR11
    #define __CAITLYN_NOEXCEPT11
#endif

#if __CAITLYN_CXX_STANDARD >= __CAITLYN_CXX_STANDARD14_VERSION
    #define __CAITLYN_HAS_CXX14 1
    #define __CAITLYN_CONSTEXPR14 constexpr
#else
    #define __CAITLYN_HAS_CXX14 0
    #define __CAITLYN_CONSTEXPR14
#endif

#if __CAITLYN_CXX_STANDARD >= __CAITLYN_CXX_STANDARD17_VERSION
    #define __CAITLYN_HAS_CXX17 1
    #define __CAITLYN_CONSTEXPR17 constexpr
    #define __CAITLYN_INLINE17 inline
    #define __CAITLYN_NODISCARD17 [[nodiscard]]
#else
    #define __CAITLYN_HAS_CXX17 0
    #define __CAITLYN_CONSTEXPR17
    #define __CAITLYN_INLINE17
    #define __CAITLYN_NODISCARD17
#endif

#if __CAITLYN_CXX_STANDARD >= __CAITLYN_CXX_STANDARD20_VERSION
    #define __CAITLYN_HAS_CXX20 1
    #define __CAITLYN_CONSTEXPR20 constexpr
    #define __CAITLYN_CONSTEVAL20 consteval
    #define __CAITLYN_CONSTINIT20 constinit
    #define __CAITLYN_NODISCARD20(x) [[nodiscard(__CAITLYN_TOSTRING(x))]]
#else
    #define __CAITLYN_HAS_CXX20 0
    #define __CAITLYN_CONSTEXPR20
    #define __CAITLYN_CONSTEVAL20
    #define __CAITLYN_CONSTINIT20
    #define __CAITLYN_NODISCARD20(x)
#endif

#if __CAITLYN_CXX_STANDARD >= __CAITLYN_CXX_STANDARD23_VERSION
    #define __CAITLYN_HAS_CXX23 1
    #define __CAITLYN_CONSTEXPR23 constexpr
#else
    #define __CAITLYN_HAS_CXX23 0
    #define __CAITLYN_CONSTEXPR23
#endif

#ifdef __CAITLYN_OS_WINDOWS
    #if defined(__CAITLYN_COMPILER_MSVC) || defined(__CAITLYN_COMPILER_CLANG)
        #define NOMINMAX
    #endif
    #include <windows.h>
#endif

#include "Caitlyn/__Caitlyn/Namespace.h"

#endif //CAITLYN_CONFIG_H_
