// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ERROR_TYPES_ERROR_H_
#define CAITLYN_CORE_ERROR_TYPES_ERROR_H_

#include "caitlyn/core/core.h"

BEGIN_CAITLYN_NS

template <typename E>
class error_t {
public:
  explicit error_t(E error) : error_{std::move(error)} {}
  const E& get() const noexcept { return error_; }

private:
  E error_;
};

template <typename E>
bool operator==(const error_t<E>& lhs, const error_t<E>& rhs) {
  return lhs.get() == rhs.get();
}

template <typename E>
bool operator!=(const error_t<E>& lhs, const error_t<E>& rhs) {
  return !(lhs == rhs);
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_ERROR_TYPES_ERROR_H_
