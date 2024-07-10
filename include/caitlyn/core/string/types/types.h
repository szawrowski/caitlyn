// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_TYPES_TYPES_H_
#define CAITLYN_CORE_STRING_TYPES_TYPES_H_

#include <sstream>

#include "caitlyn/core/core.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd14_ver)
  using namespace std::literals::string_literals;
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  using namespace std::literals::string_view_literals;
#endif

__caitlyn_begin_global_namespace

using string_t = std::basic_string<char_t>;
using xstring_t = std::basic_string<xchar_t>;
using u8string_t = std::basic_string<u8char_t>;
using u16string_t = std::basic_string<u16char_t>;
using u32string_t = std::basic_string<u32char_t>;

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
using strview_t = std::basic_string_view<char_t>;
using xstrview_t = std::basic_string_view<xchar_t>;
using u8strview_t = std::basic_string_view<u8char_t>;
using u16strview_t = std::basic_string_view<u16char_t>;
using u32strview_t = std::basic_string_view<u32char_t>;
#endif

using istrstream_t = std::basic_istringstream<char_t>;
using ostrstream_t = std::basic_ostringstream<char_t>;
using strstream_t = std::basic_stringstream<char_t>;

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_STRING_TYPES_TYPES_H_
