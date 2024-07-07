// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_CORE_MEMORY_RAW_POINTER_H_
#define CAITLYN_CORE_MEMORY_RAW_POINTER_H_

#include "caitlyn/core/defs/basic_types.h"

BEGIN_CAITLYN_NS

template <typename T>
class ptr_t final {
public:
  using value_type = T;
  using pointer = T*;
  using const_pointer = const T*;
  using reference = T&;

public:
  ptr_t() = default;
  ptr_t(const_pointer data) : data_{data} {}
  ptr_t(const ptr_t& other) : data_{other.data_} {}

public:
  ptr_t& operator=(pointer data) {
    this->data_ = data;
    return *this;
  }

  ptr_t& operator=(const ptr_t& other) {
    this->data_ = other.data_;
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
  bool operator==(const ptr_t& other) const { return data_ == other.data_; }
  bool operator!=(const ptr_t& other) const { return data_ != other.data_; }

  bool operator==(null_t) const { return data_ == nullptr; }
  bool operator!=(null_t) const { return data_ != nullptr; }

public:
  void reset(pointer new_data = nullptr) {
    delete data_;
    data_ = new_data;
  }

  void destroy() {
    delete data_;
    data_ = nullptr;
  }

private:
  pointer data_{};
};

END_CAITLYN_NS

#endif  // CAITLYN_CORE_MEMORY_RAW_POINTER_H_