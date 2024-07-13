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

#ifndef CAITLYN_CORE_MEMORY_TYPES_WEAK_POINTER_H
#define CAITLYN_CORE_MEMORY_TYPES_WEAK_POINTER_H

#include "caitlyn/core/memory/types/shared_pointer.h"

namespace cait {

template <typename T>
class wptr_t {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using resource_type = sptr_t<T>;

public:
  wptr_t() : data_(nullptr) {}
  wptr_t(const resource_type& resource) : data_{resource} {}
  wptr_t(const wptr_t& other) : data_{other.data_} {}
  wptr_t(wptr_t&& other) noexcept : data_{std::move(other.data_)} {}

public:
  wptr_t& operator=(const wptr_t& other) {
    data_ = other.data_;
    return *this;
  }

  wptr_t& operator=(const resource_type& sp) {
    this->data_ = sp;
    return *this;
  }

  wptr_t& operator=(wptr_t&& other) noexcept {
    data_ = std::move(other.data_);
    return *this;
  }

public:
  reference operator*() const {
    if (data_ == nullptr || !data_.get()) {
      throw std::runtime_error{"Dereferencing null or expired weak pointer."};
    }
    return *data_;
  }

  pointer operator->() const {
    if (data_ == nullptr || !data_.get()) {
      throw std::runtime_error{"Dereferencing null or expired weak pointer."};
    }
    return data_.get();
  }

public:
  bool operator==(const wptr_t& other) const { return data_ == other.data_; }
  bool operator!=(const wptr_t& other) const { return data_ != other.data_; }

  bool operator==(null_t) const { return data_ == nullptr; }
  bool operator!=(null_t) const { return data_ != nullptr; }

public:
  resource_type lock() const {
    if (data_ == nullptr || !data_.get()) {
      return resource_type();
    }
    return data_;
  }

public:
  __caitlyn_nodiscard bool expired() const {
    return data_ == nullptr || !data_.get();
  }

private:
  resource_type data_;
};

}  // namespace cait

#endif  // CAITLYN_CORE_MEMORY_TYPES_WEAK_POINTER_H
