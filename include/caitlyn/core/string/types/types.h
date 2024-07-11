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

#ifndef CAITLYN_CORE_STRING_TYPES_TYPES_H_
#define CAITLYN_CORE_STRING_TYPES_TYPES_H_

#include <sstream>

#include "caitlyn/__detail.h"

#if __caitlyn_has_cxx14
  using namespace std::literals::string_literals;
#endif
#if __caitlyn_has_cxx17
  using namespace std::literals::string_view_literals;
#endif

namespace cait {

using string_t = std::basic_string<char_t>;
using xstring_t = std::basic_string<xchar_t>;
using u8string_t = std::basic_string<u8char_t>;
using u16string_t = std::basic_string<u16char_t>;
using u32string_t = std::basic_string<u32char_t>;
#if __caitlyn_has_cxx17
using strview_t = std::basic_string_view<char_t>;
using xstrview_t = std::basic_string_view<xchar_t>;
using u8strview_t = std::basic_string_view<u8char_t>;
using u16strview_t = std::basic_string_view<u16char_t>;
using u32strview_t = std::basic_string_view<u32char_t>;
#endif

using istrstream_t = std::basic_istringstream<char_t>;
using ostrstream_t = std::basic_ostringstream<char_t>;
using strstream_t = std::basic_stringstream<char_t>;

}  // namespace cait

#endif  // CAITLYN_CORE_STRING_TYPES_TYPES_H_
