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

#ifndef CAITLYN_CORE_UTILITY_H_
#define CAITLYN_CORE_UTILITY_H_

#include <bitset>
#include <csetjmp>
#include <csignal>
#include <cstdarg>
#include <cstddef>
#include <cstdlib>
#include <functional>
#include <initializer_list>
#include <regex>
#include <tuple>
#include <type_traits>
#include <typeindex>
#include <typeinfo>
#include <utility>

#include "Caitlyn/__Core/Utility/Comparators.h"
#include "Caitlyn/__Core/Utility/Random.h"

#if __caitlyn_has_cxx17
    #include <any>
    #include <optional>
    #include <variant>
#endif

#if __caitlyn_has_cxx20
    #include <source_location>
    #include <version>
#endif

#endif // CAITLYN_CORE_UTILITY_H_
