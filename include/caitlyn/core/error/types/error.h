// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ERROR_TYPES_ERROR_H_
#define CAITLYN_CORE_ERROR_TYPES_ERROR_H_

#include <caitlyn/core/string/defs/string_definitions.h>

BEGIN_CAITLYN_NS

template <typename E>
class error_t {
public:
  explicit error_t(E error) : error_{std::move(error)} {}
  [[nodiscard]] const E& get() const noexcept { return error_; }

private:
  E error_;
};

template <typename E>
static error_t<E> make_error(E error) {
  return error_t<E>(error);
}

static error_t<string_t> make_error(const char_t* error) {
  return error_t(string_t{error});
}

static error_t<string_t> make_error(const string_t& error) {
  return error_t(error);
}

END_CAITLYN_NS

template <typename E>
bool operator==(const cait::error_t<E>& lhs, const cait::error_t<E>& rhs) {
  return lhs.get() == rhs.get();
}

template <typename E>
bool operator!=(const cait::error_t<E>& lhs, const cait::error_t<E>& rhs) {
  return !(lhs == rhs);
}



#endif  // CAITLYN_CORE_ERROR_TYPES_ERROR_H_
