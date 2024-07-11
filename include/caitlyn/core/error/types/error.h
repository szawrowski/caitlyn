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

#ifndef CAITLYN_CORE_ERROR_TYPES_ERROR_H_
#define CAITLYN_CORE_ERROR_TYPES_ERROR_H_

#include "caitlyn/core/string.h"

namespace cait {

template <typename E>
class error_t {
public:
  explicit error_t(E error) : error_{std::move(error)} {}
  __caitlyn_nodiscard const E& get() const noexcept { return error_; }

private:
  E error_;
};

template <typename E>
static error_t<E> make_error(E error) {
  return error_t<E>(error);
}

static error_t<string_t> make_error(const char_t* error) {
  return error_t<string_t>(string_t{error});
}

static error_t<string_t> make_error(const string_t& error) {
  return error_t<string_t>(error);
}

}  // namespace cait

template <typename E>
bool operator==(const cait::error_t<E>& lhs, const cait::error_t<E>& rhs) {
  return lhs.get() == rhs.get();
}

template <typename E>
bool operator!=(const cait::error_t<E>& lhs, const cait::error_t<E>& rhs) {
  return !(lhs == rhs);
}

#endif  // CAITLYN_CORE_ERROR_TYPES_ERROR_H_
