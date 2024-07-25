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

#ifndef CAITLYN_CORE_ERROR_H_
#define CAITLYN_CORE_ERROR_H_

#include <cassert>
#include <cerrno>
#include <exception>
#include <stdexcept>
#include <system_error>

#include "caitlyn/__core/error/expected.h"
#include "caitlyn/__core/error/unexpected.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T, typename E>
using expected = error::expected_t<T, E>;

template <typename E>
using unexpected = error::unexpected_t<E>;

__CAITLYN_GLOBAL_NAMESPACE_END

#if __CAITLYN_HAS_CXX20
    #include <stacktrace>
#endif

#if __CAITLYN_HAS_CXX23
    #include <expected>
#endif

#endif // CAITLYN_CORE_ERROR_H_
