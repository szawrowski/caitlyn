// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_H_
#define CAITLYN_SER_JSON_TYPES_JSON_H_

#include "caitlyn/core/io.h"
#include "caitlyn/ser/json/types/parser.h"
#include "caitlyn/ser/json/utility/utility.h"

namespace cait {

class json_t {
public:
  using error_type = json::error_t;
  using data_type = json::__detail::data_t;
  using parser_type = json::__detail::parser_t;

public:
  json_t() = default;
  json_t(const std::string& value) { parse(value); }
  json_t(const std::ifstream& stream) { parse(stream); }
  json_t(const json_t& other) : root_{other.root_}, error_{other.error_} {}
  json_t(json_t&& other) noexcept
      : root_{std::move(other.root_)}, error_{other.error_} {
    other.root_ = json::make_null();
    other.error_ = json::error_t::no_error;
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
      other.root_ = json::make_null();
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
    if (const auto parser = parser_type::parse(value); parser.has_error()) {
      error_ = parser.get_error();
      root_ = json::make_null();
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
                    [&key](const auto& pair) { return pair.first == key; }),
                obj.end());
    }
  }

  __caitlyn_nodiscard bool has_member(const std::string& key) const {
    return root_.has_member(key);
  }

  __caitlyn_nodiscard size_t size() const { return root_.size(); }

  __caitlyn_nodiscard bool has_error() const {
    return error_ != error_type::no_error;
  }

  __caitlyn_nodiscard error_type get_error() const { return error_; }

  __caitlyn_nodiscard std::string get_error_string() const {
    return json::get_error_string(error_);
  }

  __caitlyn_nodiscard json::class_t get_type() const {
    return root_.get_type();
  }

  __caitlyn_nodiscard std::string to_string(const bool mangling = false,
                                      const size_t indent = 2) const {
    return root_.to_string(mangling, indent);
  }

private:
  data_type root_{json::make_object()};
  error_type error_{error_type::no_error};
};

static json_t make_json() { return json_t{}; }

static json_t make_json(const std::string& value) { return json_t{value}; }

static json_t make_json(const json_t& value) { return json_t{value}; }

static json_t make_json(json_t&& value) { return json_t{std::move(value)}; }

static json_t make_json(const std::ifstream& stream) { return json_t{stream}; }

}  // namespace cait

static std::istream& operator>>(std::istream& is, cait::json_t& value) {
  std::ostringstream buffer;
  buffer << is.rdbuf();
  value.parse(buffer.str());
  return is;
}

static std::ostream& operator<<(std::ostream& os, const cait::json_t& value) {
  os << value.to_string();
  return os;
}

#endif  // CAITLYN_SER_JSON_TYPES_JSON_H_
