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

#ifndef CAITLYN_CORE_MEMORY_TYPES_RAW_POINTER_H_
#define CAITLYN_CORE_MEMORY_TYPES_RAW_POINTER_H_

#include <stdexcept>

namespace cait {

template <typename T>
class ptr_t final {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;

public:
  ptr_t() = default;
  ptr_t(pointer data) : data_{data} {}
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

  bool operator==(std::nullptr_t) const { return data_ == nullptr; }
  bool operator!=(std::nullptr_t) const { return data_ != nullptr; }

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

}  // namespace cait

#endif  // CAITLYN_CORE_MEMORY_TYPES_RAW_POINTER_H_
