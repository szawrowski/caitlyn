// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_
#define CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_

#include <sstream>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename CharT>
using std_basic_string = std::basic_string<CharT>;

using std_string_t = std_basic_string<u8char_t>;
using std_xstring_t = std_basic_string<xchar_t>;
using std_u8string_t = std_basic_string<u8char_t>;
using std_u16string_t = std_basic_string<u16char_t>;
using std_u32string_t = std_basic_string<u32char_t>;

using istrstream_t = std::basic_istringstream<u8char_t>;
using ostrstream_t = std::basic_ostringstream<u8char_t>;
using strstream_t = std::basic_stringstream<u8char_t>;

END_CAITLYN_NS

#endif  // CAITLYN_CORE_STRING_DEFS_STRING_DEFINITIONS_H_
