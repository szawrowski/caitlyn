// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_
#define CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_

#include <sstream>

#include "caitlyn/core/defs/basic_types.h"

#if (__caitlyn_cxxstd >= __caitlyn_cxxstd14_ver)
  using namespace std::literals::string_literals;
#endif
#if (__caitlyn_cxxstd >= __caitlyn_cxxstd17_ver)
  using namespace std::literals::string_view_literals;
#endif

BEGIN_CAITLYN_NS

template <typename CharT>
using basic_string_t = std::basic_string<CharT>;
using string_t = basic_string_t<u8char_t>;
using xstring_t = basic_string_t<xchar_t>;
using u8string_t = basic_string_t<u8char_t>;
using u16string_t = basic_string_t<u16char_t>;
using u32string_t = basic_string_t<u32char_t>;

template <typename CharT>
using basic_strview_t = std::basic_string_view<CharT>;
using strview_t = basic_strview_t<u8char_t>;
using xstrview_t = basic_strview_t<xchar_t>;
using u8strview_t = basic_strview_t<u8char_t>;
using u16strview_t = basic_strview_t<u16char_t>;
using u32strview_t = basic_strview_t<u32char_t>;

template <typename CharT>
using basic_istrstream_t = std::basic_istringstream<CharT>;
using istrstream_t = basic_istrstream_t<u8char_t>;

template <typename CharT>
using basic_ostrstream_t = std::basic_ostringstream<CharT>;
using ostrstream_t = basic_ostrstream_t<u8char_t>;

template <typename CharT>
using basic_strstream_t = std::basic_stringstream<CharT>;
using strstream_t = basic_strstream_t<u8char_t>;

END_CAITLYN_NS

#endif  // CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_
