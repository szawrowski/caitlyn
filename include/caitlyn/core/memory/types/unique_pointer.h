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

#ifndef CAITLYN_CORE_MEMORY_TYPES_UNIQUE_POINTER_H
#define CAITLYN_CORE_MEMORY_TYPES_UNIQUE_POINTER_H

namespace cait {

template <typename T>
class uptr_t {
public:
  using value_type = T;
  using pointer = T*;
  using reference = T&;

public:
  uptr_t() = default;
  uptr_t(pointer data) : data_{data} {}
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

  bool operator==(std::nullptr_t) const { return data_ == nullptr; }
  bool operator!=(std::nullptr_t) const { return data_ != nullptr; }

public:
  void reset(pointer new_data = nullptr) {
    if (data_ != new_data) {
      delete data_;
      data_ = new_data;
    }
  }

  pointer release() {
    pointer tmp = data_;
    data_ = nullptr;
    return tmp;
  }

private:
  pointer data_{};
};

}  // namespace cait

#endif  // CAITLYN_CORE_MEMORY_TYPES_UNIQUE_POINTER_H
