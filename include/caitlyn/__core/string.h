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

#ifndef CAITLYN_CORE_STRING_H_
#define CAITLYN_CORE_STRING_H_

#include <cctype>
#include <cwchar>
#include <cwctype>
#include <cuchar>
#include <cstring>
#include <sstream>
#include <string>

#include "caitlyn/__core/string/algo.h"
#include "caitlyn/__core/string/defs.h"
#include "caitlyn/__core/string/utility.h"
#include "caitlyn/__core/string/types.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

using string = basic_string_t<char>;

__CAITLYN_GLOBAL_NAMESPACE_END

#if __CAITLYN_HAS_CXX11 && !__CAITLYN_HAS_CXX17
  #include <codecvt>
#endif

#if __CAITLYN_HAS_CXX14
using namespace std::literals::string_literals;
#endif

#if __CAITLYN_HAS_CXX17
using namespace std::literals::string_view_literals;
#endif

#if __CAITLYN_HAS_CXX17
  #include <charconv>
#endif

#endif  // CAITLYN_CORE_STRING_H_
