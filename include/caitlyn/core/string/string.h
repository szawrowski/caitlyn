// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_STRING_STRING_H_
#define CAITLYN_CORE_STRING_STRING_H_

#include <cstring>
#include <sstream>
#include <string>

#include "caitlyn/core/format/format.h"
#include "caitlyn/core/string/algo/algo.h"
#include "caitlyn/core/string/text/text.h"
#include "caitlyn/core/string/types/types.h"
#include "caitlyn/core/string/utility/utility.h"
#include "caitlyn/core/unicode/unicode.h"

#if __caitlyn_has_cxx11 && !(__caitlyn_has_cxx17)
  #include <codecvt>
#endif

#if __caitlyn_has_cxx20
  #include <format>
#endif

namespace cait {

using unichar_t = unicode_char<u8char_t>;
using unistring_t = unicode_string<unicode_char<u8char_t>>;

using text_t = text_builder_t<u8char_t>;

}  // namespace cait



#endif  // CAITLYN_CORE_STRING_STRING_H_
