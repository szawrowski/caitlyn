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

#ifndef CAITLYN_CORE_ERROR_TYPES_RESULT_H_
#define CAITLYN_CORE_ERROR_TYPES_RESULT_H_

#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>

#include "caitlyn/core/error/types/error.h"
#include "caitlyn/core/traits.h"
#include "caitlyn/core/utility.h"

namespace cait {

template <typename T, typename E>
class result_t {
public:
  using value_type = T;
  using error_type = E;

  result_t(const value_type& value) : has_value_(true) {
    new (&data_.value) value_type(value);
  }

  result_t(value_type&& value) : has_value_(true) {
    new (&data_.value) value_type(std::move(value));
  }

  result_t(const error_t<error_type>& error) : has_value_(false) {
    new (&data_.error) error_t<error_type>(error);
  }

  result_t(error_t<error_type>&& error) : has_value_(false) {
    new (&data_.error) error_t<error_type>(std::move(error));
  }

  result_t(const result_t& other) : has_value_(other.has_value_) {
    if (has_value_) {
      new (&data_.value) value_type(other.data_.value);
    } else {
      new (&data_.error) error_t<error_type>(other.data_.error);
    }
  }

  result_t& operator=(const result_t& other) {
    if (this != &other) {
      destroy_union();
      has_value_ = other.has_value_;
      if (has_value_) {
        new (&data_.value) value_type(other.data_.value);
      } else {
        new (&data_.error) error_t<error_type>(other.data_.error);
      }
    }
    return *this;
  }

  result_t(result_t&& other) noexcept(
      std::is_nothrow_move_constructible<value_type>::value &&
      std::is_nothrow_move_constructible<error_type>::value)
      : has_value_(other.has_value_) {
    if (has_value_) {
      new (&data_.value) value_type(std::move(other.data_.value));
    } else {
      new (&data_.error) error_t<error_type>(std::move(other.data_.error));
    }
  }

  result_t& operator=(result_t&& other) noexcept(
      std::is_nothrow_move_assignable<value_type>::value &&
      std::is_nothrow_move_assignable<error_type>::value) {
    if (this != &other) {
      destroy_union();
      has_value_ = other.has_value_;
      if (has_value_) {
        new (&data_.value) value_type(std::move(other.data_.value));
      } else {
        new (&data_.error) error_t<error_type>(std::move(other.data_.error));
      }
    }
    return *this;
  }

  ~result_t() { destroy_union(); }

  explicit operator bool() const noexcept { return has_value_; }

  __caitlyn_nodiscard bool has_value() const noexcept { return has_value_; }

  __caitlyn_nodiscard bool has_error() const noexcept { return !has_value_; }

  const value_type& get() const {
    if (has_value_) {
      return data_.value;
    }
    throw std::logic_error{"Called get() on an error result"};
  }

  const error_type& get_error() const {
    if (!has_value_) {
      return data_.error.get();
    }
    throw std::logic_error{"Called get_error() on a non-error result"};
  }

  template <typename Func>
  auto map(Func func) const
      -> result_t<typename std::result_of<Func(const value_type&)>::type,
                  error_type> {
    using result_value_type =
        typename std::result_of<Func(const value_type&)>::type;
    if (has_value_) {
      return result_t<result_value_type, error_type>(func(data_.value));
    }
    return result_t<result_value_type, error_type>(data_.error);
  }

  template <typename Func>
  auto map_error(Func func) const
      -> result_t<value_type,
                  typename std::result_of<Func(const error_type&)>::type> {
    using result_error_type =
        typename std::result_of<Func(const error_type&)>::type;
    if (!has_value_) {
      return result_t<value_type, result_error_type>(
          error_t<result_error_type>(func(data_.error.get())));
    }
    return *this;
  }

  template <typename Func>
  auto and_then(Func func) const -> result_t {
    if (has_value_) {
      return func(data_.value);
    }
    return *this;
  }

  template <typename Func>
  auto or_else(Func func) const -> result_t {
    if (!has_value_) {
      return func(data_.error.get());
    }
    return *this;
  }

  template <typename U>
  value_type unwrap_or(const U& value) const {
    if (has_value_) {
      return data_.value;
    }
    return value;
  }

  template <typename ErrFunc>
  auto unwrap_or_else(ErrFunc func) const
      -> decltype(func(std::declval<error_t<error_type>>().get())) {
    if (has_value_) {
      return data_.value;
    }
    return func(data_.error.get());
  }

  const value_type& unwrap_or_default() const {
    static value_type default_value{};
    return unwrap_or(default_value);
  }

  const value_type& unwrap_or_default(const value_type& default_value) const {
    return unwrap_or(default_value);
  }

  const value_type& expect(const std::string& message) const {
    if (has_value_) {
      return data_.value;
    }
    throw std::runtime_error(message);
  }

  template <typename U>
  auto expect_error(const U& message) const -> const error_type& {
    if (!has_value_) {
      return data_.error.get();
    }
    throw std::runtime_error(message);
  }

  template <typename Func>
  auto filter(Func func) const -> result_t {
    if (has_value_ && func(data_.value)) {
      return *this;
    }
    return result_t(error_t<error_type>{});
  }

  template <typename U, typename Func>
  auto fold(U&& init, Func&& f) const
      -> decltype(f(std::declval<U>(), std::declval<value_type>())) {
    if (has_value_) {
      return f(std::forward<U>(init), data_.value);
    }
    return std::forward<U>(init);
  }

  template <typename Func>
  auto then(Func func) const -> result_t {
    if (has_value_) {
      return func(data_.value);
    }
    return *this;
  }

  template <typename Func>
  auto catch_error(Func func) const -> result_t {
    if (!has_value_) {
      return func(data_.error.get());
    }
    return *this;
  }

  template <typename Func>
  auto on_error(Func func) const -> result_t {
    if (!has_value_) {
      func(data_.error.get());
    }
    return *this;
  }

  template <typename Func>
  auto customize(Func&& func) const -> decltype(func(*this)) {
    return func(*this);
  }

  template <typename TFunc, typename EFunc, typename... Args>
  auto inspect(TFunc value_func, EFunc error_func, Args&&... args) const
      -> decltype(value_func(std::declval<value_type>(),
                             std::forward<Args>(args)...)) {
    if (has_value_) {
      return value_func(data_.value, std::forward<Args>(args)...);
    }
    return error_func(data_.error.get(), std::forward<Args>(args)...);
  }

private:
  template <typename ResultT = value_type, typename ErrorT = error_type>
  typename std::enable_if<has_destructor<ResultT>::value &&
                          !has_destructor<ErrorT>::value>::type
  destroy_union() {
    if (has_value_) {
      data_.value.~value_type();
    }
  }

  template <typename ResultT = value_type, typename ErrorT = error_type>
  typename std::enable_if<!has_destructor<ResultT>::value &&
                          has_destructor<ErrorT>::value>::type
  destroy_union() {
    if (!has_value_) {
      data_.error.~error_t<error_type>();
    }
  }

  template <typename ResultT = value_type, typename ErrorT = error_type>
  typename std::enable_if<has_destructor<ResultT>::value &&
                          has_destructor<ErrorT>::value>::type
  destroy_union() {
    if (has_value_) {
      data_.value.~value_type();
    } else {
      data_.error.~error_t<error_type>();
    }
  }

  template <typename ResultT = value_type, typename ErrorT = error_type>
  typename std::enable_if<!has_destructor<ResultT>::value &&
                          !has_destructor<ErrorT>::value>::type
  destroy_union() {}

private:
  union data_union {
    value_type value;
    error_t<error_type> error;

    data_union() {}
    ~data_union() {}
  } data_;

  bool has_value_;
};

template <typename T, typename E>
static result_t<T, E> make_result(T value) {
  return result_t<T, E>(std::move(value));
}

}  // namespace cait

#endif  // CAITLYN_CORE_ERROR_TYPES_RESULT_H_
