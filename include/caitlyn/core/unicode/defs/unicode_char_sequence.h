// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_UNICODE_DEFS_UNICODE_CHAR_SEQUENCE_H_
#define CAITLYN_CORE_UNICODE_DEFS_UNICODE_CHAR_SEQUENCE_H_

#include <tuple>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename CharT>
class char_seq_t;

template <>
class char_seq_t<u8char_t> {
public:
  using value_type = u8char_t;
  using type = std::tuple<u8char_t, u8char_t, u8char_t, u8char_t>;
};

END_CAITLYN_NS

#endif  // CAITLYN_CORE_UNICODE_DEFS_UNICODE_CHAR_SEQUENCE_H_
