// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_DEFS_BASIC_TYPE_LITERALS_H_
#define CAITLYN_CORE_DEFS_BASIC_TYPE_LITERALS_H_

#include "caitlyn/core/defs/basic_types.h"

inline cait::char_t operator""_c(const char val) {
  return val;
}
inline cait::uchar_t operator""_uc(const unsigned long long val) {
  return static_cast<cait::uchar_t>(val);
}
inline cait::schar_t operator""_sc(const signed long long val) {
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
inline cait::size_t operator""_uz(const unsigned long long val) {
  return static_cast<cait::size_t>(val);
}
inline cait::ssize_t operator""_sz(const unsigned long long val) {
  return static_cast<cait::ssize_t>(val);
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

#endif  // CAITLYN_CORE_DEFS_BASIC_TYPE_LITERALS_H_
