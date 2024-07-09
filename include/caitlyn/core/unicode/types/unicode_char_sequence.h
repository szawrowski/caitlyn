// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_
#define CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_

#include "caitlyn/core/utility/types/types.h"

__caitlyn_begin_global_namespace

template <typename CharT>
class char_seq_t;

template <>
class char_seq_t<u8char_t> {
public:
  using value_type = u8char_t;
  using type = tuple_t<u8char_t, u8char_t, u8char_t, u8char_t>;
};

__caitlyn_end_global_namespace

#endif  // CAITLYN_CORE_UNICODE_TYPES_UNICODE_CHAR_SEQUENCE_H_
