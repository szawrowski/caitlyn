// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_H_
#define CAITLYN_SER_JSON_TYPES_JSON_H_

#include "caitlyn/core/io.h"
#include "caitlyn/ser/json/types/json_parser.h"
#include "caitlyn/ser/json/utility/json_error_strings.h"

BEGIN_CAITLYN_NS

class json_t {
public:
  using json_data_type = __detail::json_data_t;
  using json_parser_type = __detail::json_parser_t;
  using size_type = size_t;

public:
  json_t() = default;
  json_t(const string_t& value) { parse(value); }
  json_t(const ifstream_t& stream) { parse(stream); }
  json_t(const json_t& other) : root_{other.root_}, error_{other.error_} {}
  json_t(json_t&& other) noexcept
      : root_{std::move(other.root_)}, error_{std::move(other.error_)} {
    other.root_ = json::make_null();
    other.error_ =
        std::make_pair(json_parse_error_t::no_error, max_value<size_type>());
  }

  ~json_t() = default;

public:
  json_t& operator=(const string_t& value) {
    parse(value);
    return *this;
  }

  json_t& operator=(const ifstream_t& stream) {
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
      other.error_ = std::make_pair(json_parse_error_t::no_error, 0);
    }
    return *this;
  }

public:
  json_data_type& operator[](const string_t& key) { return root_[key]; }

  const json_data_type& operator[](const string_t& key) const {
    return root_.at(key);
  }

public:
  void parse(const string_t& value) {
    if (const auto parser = json_parser_type::parse(value);
        parser.has_error()) {
      error_ = parser.get_error();
      root_ = json::make_null();
    } else {
      error_ = std::make_pair(json_parse_error_t::no_error, 0);
      root_ = parser.get_data();
    }
  }

  void parse(const ifstream_t& ifs) {
    ostrstream_t buffer;
    buffer << ifs.rdbuf();
    parse(buffer.str());
  }

  void add_member(const string_t& key, const json_data_type& value) {
    root_[key] = value;
  }

  void add_member(const vector_t<string_t>& keys, const json_data_type& value) {
    json_data_type* current = &root_;

    // Traverse through keys to navigate the nested structure
    for (const auto& key : keys) {
      if (current->is_array() && is_number(key)) {
        // Convert key to array index if current object is an array
        const size_t index = std::stoull(key);
        // Expand the array if index is greater than current size
        while (index >= current->size()) {
          current->append(json_data_type{});
        }
        // Move to the new array element
        current = &(*current)[index];
      } else {
        // Access by key if current object is an object
        current = &(*current)[key];
      }
    }
    // Assign the value at the end of navigation
    *current = value;
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

  [[nodiscard]] bool_t has_member(const string_t& key) const {
    return root_.has_member(key);
  }

  [[nodiscard]] size_type size() const { return root_.size(); }

  [[nodiscard]] bool_t has_error() const {
    return error_.first != json_parse_error_t::no_error;
  }

  [[nodiscard]] json_parse_error_t get_error() const { return error_.first; }

  [[nodiscard]] auto get_error_string() const {
    return get_json_parse_error_string(error_);
  }

  [[nodiscard]] json_class_t get_type() const { return root_.get_type(); }

  [[nodiscard]] string_t to_string(const bool_t mangling = false,
                                   const size_type indent = 2) const {
    return root_.to_string(mangling, indent);
  }

private:
  json_data_type root_{json::make_object()};
  pair_t<json_parse_error_t, size_type> error_{json_parse_error_t::no_error, 0};
};

static json_t make_json() { return json_t{}; }

static json_t make_json(const string_t& value) { return json_t{value}; }

static json_t make_json(const json_t& value) { return json_t{value}; }

static json_t make_json(json_t&& value) { return json_t{std::move(value)}; }

static json_t make_json(const ifstream_t& stream) { return json_t{stream}; }

END_CAITLYN_NS

static cait::istream_t& operator>>(cait::istream_t& is, cait::json_t& value) {
  cait::ostrstream_t buffer;
  buffer << is.rdbuf();
  value.parse(buffer.str());
  return is;
}

static cait::ostream_t& operator<<(cait::ostream_t& os,
                                   const cait::json_t& value) {
  os << value.to_string();
  return os;
}

#endif  // CAITLYN_SER_JSON_TYPES_JSON_H_
