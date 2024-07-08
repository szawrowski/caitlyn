// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_ERROR_TYPES_RESULT_H_
#define CAITLYN_CORE_ERROR_TYPES_RESULT_H_

#include <stdexcept>

#include "caitlyn/core/error/types/error.h"
#include "caitlyn/core/utility.h"

BEGIN_CAITLYN_NS

template <typename T, typename E>
class result_t {
public:
  using value_type = T;
  using error_type = E;
  using result_type = variant_t<value_type, error_t<error_type>>;

public:
  constexpr result_t(const value_type& value) : inner_(value) {}
  constexpr result_t(value_type&& value) : inner_(std::move(value)) {}
  constexpr result_t(const error_t<error_type>& error) : inner_(error) {}
  constexpr result_t(error_t<error_type>&& error) : inner_(std::move(error)) {}

  template <typename U>
  constexpr result_t(
      U&& value,
      std::enable_if_t<std::is_constructible_v<error_t<error_type>, U>>* =
          nullptr) {
    using DecayedType = std::decay_t<U>;
    if constexpr (std::is_same_v<DecayedType, value_type>) {
      inner_ = std::forward<U>(value);
    } else {
      inner_ = error_t<error_type>{std::forward<U>(value)};
    }
  }

  result_t(const result_t& other) : inner_{other.inner_} {}

  result_t& operator=(const result_t& other) {
    if (this != &other) {
      this->inner_ = other.inner_;
    }
    return *this;
  }

  constexpr result_t(result_t&& other) noexcept(
      std::is_nothrow_move_constructible_v<value_type> &&
      std::is_nothrow_move_constructible_v<error_type>)
      : inner_(std::move(other.inner_)) {}

  result_t& operator=(result_t&& other) noexcept(
      std::is_nothrow_move_assignable_v<value_type> &&
      std::is_nothrow_move_assignable_v<error_type>) {
    if (this != &other) {
      inner_ = std::move(other.inner_);
    }
    return *this;
  }

public:
  const result_type& get_inner() const { return inner_; }

public:
  constexpr bool operator==(const result_t& other) const {
    return inner_ == other.inner_;
  }

  constexpr bool operator!=(const result_t& other) const {
    return !(*this == other);
  }

  explicit operator bool() const noexcept { return has_value(); }

public:
  [[nodiscard]] constexpr bool has_value() const noexcept {
    return std::holds_alternative<value_type>(inner_);
  }

  [[nodiscard]] constexpr bool has_error() const noexcept {
    return std::holds_alternative<error_t<error_type>>(inner_);
  }

public:
  const value_type& get() const {
    if (has_value()) {
      return std::get<value_type>(inner_);
    }
    throw std::logic_error{"Called get() on an error result"};
  }

  const error_type& get_error() const {
    if (has_error()) {
      return std::get<error_t<error_type>>(inner_).get();
    }
    throw std::logic_error{"Called error_t() on a non-error result"};
  }

public:
  template <typename Func>
  auto map(Func func) const {
    if (has_value()) {
      return result_t<std::invoke_result_t<Func, const value_type&>,
                      error_type>(func(std::get<value_type>(inner_)));
    }
    return *this;
  }

  template <typename Func>
  auto map_error(Func func) const {
    if (has_error()) {
      return result_t<value_type,
                      std::invoke_result_t<Func, const error_type&>>(
          func(std::get<error_t<error_type>>(inner_).get()));
    }
    return *this;
  }

  template <typename Func>
  auto and_then(Func func) const {
    if (has_value()) {
      return func(std::get<value_type>(inner_));
    }
    return *this;
  }

  template <typename Func>
  auto or_else(Func func) const {
    if (has_error()) {
      return func(std::get<error_t<error_type>>(inner_).get());
    }
    return *this;
  }

  template <typename U>
  value_type unwrap_or(const U& value) const {
    if (has_value()) {
      return std::get<value_type>(inner_);
    }
    return value;
  }

  template <typename ErrFunc>
  auto unwrap_or_else(ErrFunc func) const {
    if (has_value()) {
      return std::get<value_type>(inner_);
    }
    return func(std::get<error_t<error_type>>(inner_).get());
  }

  const value_type& unwrap_or_default() const {
    static value_type default_value{};
    return unwrap_or(default_value);
  }

  const value_type& unwrap_or_default(const value_type& default_value) const {
    return unwrap_or(default_value);
  }

  const value_type& expect(const std::string& message) const {
    if (has_value()) {
      return std::get<value_type>(inner_);
    }
    throw std::runtime_error(message);
  }

  template <typename U>
  auto expect_error(const U& message) const {
    if (has_error()) {
      return std::get<error_t<error_type>>(inner_).get();
    }
    throw std::runtime_error(message);
  }

  template <typename Func>
  auto filter(Func func) const {
    if (has_value() && func(std::get<value_type>(inner_))) {
      return *this;
    }
    return result_t{error_t<error_type>{}};
  }

  template <typename U, typename Func>
  auto fold(U&& init, Func&& f) const {
    if (has_value()) {
      return std::forward<Func>(f)(std::forward<U>(init),
                                   std::get<value_type>(inner_));
    }
    return std::forward<U>(init);
  }

  template <typename Func>
  auto then(Func func) const {
    if (has_value()) {
      return func(std::get<value_type>(inner_));
    }
    return *this;
  }

  template <typename Func>
  auto catch_error(Func func) const {
    if (has_error()) {
      return func(std::get<error_t<error_type>>(inner_).get());
    }
    return *this;
  }

  template <typename Func>
  auto on_error(Func func) const {
    if (has_error()) {
      func(std::get<error_t<error_type>>(inner_).get());
    }
    return *this;
  }

  template <typename Func>
  auto customize(Func&& func) const {
    return func(*this);
  }

  template <typename TFunc, typename EFunc, typename... Args>
  auto inspect(TFunc value_func, EFunc error_func, Args&&... args) const {
    if (has_value()) {
      return std::invoke(std::forward<TFunc>(value_func),
                         std::get<value_type>(inner_),
                         std::forward<Args>(args)...);
    }
    return std::invoke(std::forward<EFunc>(error_func),
                       std::get<error_t<error_type>>(inner_).get(),
                       std::forward<Args>(args)...);
  }

private:
  result_type inner_;
};

template <typename T, typename E>
static result_t<T, E> make_result(T value) {
  return value;
}

END_CAITLYN_NS

#endif  // CAITLYN_CORE_ERROR_TYPES_RESULT_H_