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

#ifndef CAITLYN_CORE_MEMORY_TYPES_SHARED_POINTER_H
#define CAITLYN_CORE_MEMORY_TYPES_SHARED_POINTER_H

#include <stdexcept>
#include <atomic>

namespace cait {

template <typename T>
class sptr_t {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;
  using counter = std::atomic_size_t;

public:
  sptr_t() = default;
  sptr_t(pointer data) : data_{data}, ref_count_{data ? new counter(1) : nullptr} {}
  sptr_t(const sptr_t& other) : data_{other.data_}, ref_count_{other.ref_count_} {
    ref_count_->fetch_add(1, std::memory_order_relaxed);
  }
  sptr_t(sptr_t&& other) noexcept : data_{other.data_}, ref_count_{other.ref_count_} {
    other.data_ = nullptr;
    other.ref_count_ = nullptr;
  }

  ~sptr_t() {
    release();
  }

public:
  sptr_t& operator=(pointer data) {
    reset(data);
    return *this;
  }

  sptr_t& operator=(const sptr_t& other) {
    if (this != &other) {
      release();
      data_ = other.data_;
      ref_count_ = other.ref_count_;
      if (ref_count_) {
        ref_count_->fetch_add(1);
      }
    }
    return *this;
  }

  sptr_t& operator=(sptr_t&& other) noexcept {
    if (this != &other) {
      release();
      data_ = other.data_;
      ref_count_ = other.ref_count_;
      other.data_ = nullptr;
      other.ref_count_ = nullptr;
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
  bool operator==(const sptr_t& other) const { return data_ == other.data_; }
  bool operator!=(const sptr_t& other) const { return data_ != other.data_; }

  bool operator==(std::nullptr_t) const { return data_ == nullptr; }
  bool operator!=(std::nullptr_t) const { return data_ != nullptr; }

public:
  void reset(pointer data = nullptr) {
    if (data_ != data) {
      release();
      data_ = data;
      ref_count_ = data ? new counter(1) : nullptr;
    }
  }

private:
  void release() const {
    if (ref_count_ && ref_count_->fetch_sub(1, std::memory_order_relaxed) == 0) {
      delete data_;
      delete ref_count_;
    }
  }

private:
  pointer data_{};
  counter* ref_count_{};
};

}  // namespace cait

#endif  // CAITLYN_CORE_MEMORY_TYPES_SHARED_POINTER_H
