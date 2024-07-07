// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_UNIQUE_POINTER_H
#define CAITLYN_CORE_MEMORY_UNIQUE_POINTER_H

#include <stdexcept>

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename T>
class uptr_t {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;

public:
  uptr_t() = default;
  uptr_t(const_pointer data) : data_{data} {}
  uptr_t(const uptr_t& other) = delete;
  uptr_t(uptr_t&& other) noexcept : data_{other.data_} { other.data_ = nullptr; }
  ~uptr_t() { delete data_; }

public:
  uptr_t& operator=(pointer data) {
    reset(data);
    return *this;
  }

  uptr_t& operator=(uptr_t&& other) noexcept {
    if (this != &other) {
      delete data_;
      data_ = other.data_;
      other.data_ = nullptr;
    }
    return *this;
  }

public:
  reference operator*() const {
    if (data_ == nullptr) {
      throw std::runtime_error{"Dereferencing null pointer."};
    }
    return *data_;
  }

  pointer operator->() const {
    if (data_ == nullptr) {
      throw std::runtime_error{"Dereferencing null pointer."};
    }
    return data_;
  }

public:
  pointer get() const { return data_; }

public:
  bool operator==(const uptr_t& other) const { return data_ == other.data_; }
  bool operator!=(const uptr_t& other) const { return data_ != other.data_; }

  bool operator==(null_t) const { return data_ == nullptr; }
  bool operator!=(null_t) const { return data_ != nullptr; }

public:
  void reset(pointer new_data = nullptr) {
    if (data_ != new_data) {
      delete data_;
      data_ = new_data;
    }
  }

  pointer release() {
    const_pointer tmp = data_;
    data_ = nullptr;
    return tmp;
  }

private:
  pointer data_{};
};

END_CAITLYN_NS

#endif  // CAITLYN_CORE_MEMORY_UNIQUE_POINTER_H
