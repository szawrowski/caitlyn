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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_

#include <fstream>

#include "caitlyn/__serializing/json/types/parser.h"
#include "caitlyn/__serializing/json/utility.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN

class json_t {
public:
  using error_type = error_t;
  using data_type = __detail::data_t;
  using parser_type = __detail::parser_t;

public:
  json_t() = default;
  json_t(const std::string& value) { parse(value); }
  json_t(const std::ifstream& stream) { parse(stream); }
  json_t(const json_t& other) : root_{other.root_}, error_{other.error_} {}
  json_t(json_t&& other) noexcept
      : root_{std::move(other.root_)}, error_{other.error_} {
    other.root_ = make_null();
    other.error_ = error_t::no_error;
  }

  ~json_t() = default;

public:
  json_t& operator=(const std::string& value) {
    parse(value);
    return *this;
  }

  json_t& operator=(const std::ifstream& stream) {
    parse(stream);
    return *this;
  }

  json_t& operator=(const json_t& other) {
    if (this != &other) {
      root_ = other.root_;
      error_ = other.error_;
    }
    return *this;
  }

  json_t& operator=(json_t&& other) noexcept {
    if (this != &other) {
      root_ = std::move(other.root_);
      error_ = other.error_;
      other.root_ = make_null();
      other.error_ = error_type::no_error;
    }
    return *this;
  }

public:
  data_type& operator[](const std::string& key) { return root_[key]; }

  const data_type& operator[](const std::string& key) const {
    return root_.at(key);
  }

public:
  void parse(const std::string& value) {
    const auto parser = parser_type::parse(value);
    if (parser.has_error()) {
      error_ = parser.get_error();
      root_ = make_null();
    } else {
      error_ = error_type::no_error;
      root_ = parser.get_data();
    }
  }

  void parse(const std::ifstream& ifs) {
    std::ostringstream buffer;
    buffer << ifs.rdbuf();
    parse(buffer.str());
  }

  void add_member(const std::string& key, const data_type& value) {
    root_[key] = value;
  }

  void remove_member(const std::string& key) {
    if (root_.has_member(key)) {
      auto& obj = root_.get_data();
      obj.erase(std::remove_if(
                    obj.begin(), obj.end(),
                    [&key](const std::pair<const std::string&,
                                           const __detail::data_t*>& pair) {
                      return pair.first == key;
                    }),
                obj.end());
    }
  }

  bool has_member(const std::string& key) const {
    return root_.has_member(key);
  }

  size_t size() const { return root_.size(); }

  bool has_error() const { return error_ != error_type::no_error; }

  error_type get_error() const { return error_; }

  std::string get_error_string() const {
    return json::get_error_string(error_);
  }

  class_t get_type() const { return root_.get_type(); }

  std::string str(const bool mangling = false, const size_t indent = 2) const {
    return root_.str(mangling, indent);
  }

private:
  data_type root_{json::make_object()};
  error_type error_{error_type::no_error};
};

inline json_t make_document() { return json_t{}; }

inline json_t make_document(const std::string& value) { return json_t{value}; }

inline json_t make_document(const json_t& value) { return json_t{value}; }

inline json_t make_document(json_t&& value) { return json_t{std::move(value)}; }

inline json_t make_document(const std::ifstream& stream) {
  return json_t{stream};
}

__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is, cait::json::json_t& value) {
  std::ostringstream buffer;
  buffer << is.rdbuf();
  value.parse(buffer.str());
  return is;
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::json::json_t& value) {
  os << value.str();
  return os;
}

#endif  // CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_