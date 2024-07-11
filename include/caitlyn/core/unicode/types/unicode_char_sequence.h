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

#ifndef CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_
#define CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_

#include <tuple>

#include "caitlyn/__detail.h"

namespace cait {

template <typename CharT>
class char_seq_t;

template <>
class char_seq_t<u8char_t> {
public:
  using value_type = u8char_t;
  using type = std::tuple<u8char_t, u8char_t, u8char_t, u8char_t>;
};

}  // namespace cait

#endif  // CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_
