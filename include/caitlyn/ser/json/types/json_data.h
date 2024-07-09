// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_SER_JSON_TYPES_JSON_DATA_H_
#define CAITLYN_SER_JSON_TYPES_JSON_DATA_H_

#include "caitlyn/core/io.h"
#include "caitlyn/core/memory.h"
#include "caitlyn/core/string.h"
#include "caitlyn/core/utility.h"
#include "caitlyn/ser/defs/serializing_definitions.h"
#include "caitlyn/ser/json/types/json_class.h"

__caitlyn_begin_global_namespace
__caitlyn_begin_detail_namespace

class json_data_t {
public:
  using array_type = deque_t<ptr_t<json_data_t>>;
  using object_type = vector_t<pair_t<string_t, ptr_t<json_data_t>>>;
  using string_type = string_t;
  using null_type = null_t;
  using floating_type = float64_t;
  using integral_type = int64_t;
  using boolean_type = bool_t;

  using data_type = variant_t<null_type, object_type, array_type, string_type,
                              floating_type, integral_type, boolean_type>;
  using size_type = size_t;

public:
  json_data_t() = default;

  json_data_t(const json_data_t& other)
      : data_{copy_data(other)}, type_{other.type_} {}

  json_data_t(json_data_t&& other) noexcept
      : data_{std::move(other.data_)}, type_{other.type_} {
    other.data_ = null_type{};
    other.type_ = json_class_t::null;
  }

  template <typename T>
  json_data_t(
      T value,
      typename std::enable_if<std::is_same<T, boolean_type>::value>::type* =
          nullptr)
      : data_{value}, type_{json_class_t::boolean} {}

  template <typename T>
  json_data_t(
      T value,
      typename std::enable_if<std::is_integral_v<T> &&
                              !std::is_same<T, boolean_type>::value>::type* =
          nullptr)
      : data_{static_cast<integral_type>(value)},
        type_{json_class_t::integral} {}

  template <typename T>
  json_data_t(T value,
              typename std::enable_if<std::is_floating_point<T>::value>::type* =
                  nullptr)
      : data_{static_cast<floating_type>(value)},
        type_{json_class_t::floating} {}

  template <typename T>
  json_data_t(T value,
              typename std::enable_if<
                  std::is_convertible<T, string_type>::value>::type* = nullptr)
      : data_{string_type{value}}, type_{json_class_t::string} {}

  ~json_data_t() { clear_internal(); }

public:
  json_data_t& operator=(const json_data_t& other) {
    if (this != &other) {
      clear_internal();
      data_ = copy_data(other);
      type_ = other.type_;
    }
    return *this;
  }

  json_data_t& operator=(json_data_t&& other) noexcept {
    if (this != &other) {
      clear_internal();
      data_ = std::move(other.data_);
      type_ = other.type_;
      other.data_ = null_type{};
      other.type_ = json_class_t::null;
    }
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_same<T, boolean_type>::value,
                          json_data_t&>::type
  operator=(T value) {
    set_type(json_class_t::boolean);
    data_ = value;
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value &&
                              !std::is_same<T, boolean_type>::value,
                          json_data_t&>::type
  operator=(T value) {
    set_type(json_class_t::integral);
    data_ = static_cast<integral_type>(value);
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value, json_data_t&>::type
  operator=(T value) {
    set_type(json_class_t::floating);
    data_ = static_cast<floating_type>(value);
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_convertible<T, string_type>::value,
                          json_data_t&>::type
  operator=(T value) {
    set_type(json_class_t::string);
    data_ = string_type{value};
    return *this;
  }

public:
  json_data_t& operator[](const string_type& key) {
    set_type(json_class_t::object);
    const auto object = std::get_if<object_type>(&data_);
    const auto it =
        std::find_if(object->begin(), object->end(),
                     [&key](const auto& pair) { return pair.first == key; });
    if (it == object->end()) {
      object->emplace_back(key, new json_data_t{});
      return *object->back().second;
    }
    return *it->second;
  }

  json_data_t& operator[](const size_type index) {
    set_type(json_class_t::array);
    const auto array = std::get_if<array_type>(&data_);
    if (index >= array->size()) {
      array->resize(index + 1, nullptr);
    }
    if (!array->at(index).get()) {
      new (array->at(index).get()) json_data_t;
    }
    return *array->at(index);
  }

public:
  json_data_t& at(const string_type& key) { return operator[](key); }

  [[nodiscard]] const json_data_t& at(const string_type& key) const {
    const auto object = std::get_if<object_type>(&data_);
    const auto it =
        std::find_if(object->begin(), object->end(),
                     [&key](const auto& pair) { return pair.first == key; });
    if (it == object->end()) {
      throw std::out_of_range{"Key not found"};
    }
    return *it->second;
  }

  json_data_t& at(const size_type index) { return operator[](index); }

  [[nodiscard]] const json_data_t& at(const size_type index) const {
    return *std::get_if<array_type>(&data_)->at(index);
  }

public:
  template <typename T>
  void append(T arg) {
    if (!is_array()) {
      set_type(json_class_t::array);
    }
    std::get_if<array_type>(&data_)->emplace_back(new json_data_t{arg});
  }

  template <typename T, typename... U>
  void append(T arg, U... args) {
    append(arg);
    append(args...);
  }

public:
  [[nodiscard]] size_type size() const {
    if (is_array()) {
      return std::get_if<array_type>(&data_)->size();
    }
    if (is_object()) {
      return std::get_if<object_type>(&data_)->size();
    }
    return max_value<size_type>();
  }

  [[nodiscard]] size_type length() const {
    if (is_array()) {
      return std::get_if<array_type>(&data_)->size();
    }
    return max_value<size_type>();
  }

public:
  [[nodiscard]] boolean_type has_member(const string_type& key) const {
    if (is_object()) {
      const auto& object = std::get_if<object_type>(&data_);
      return std::find_if(object->begin(), object->end(),
                          [&key](const auto& pair) {
                            return pair.first == key;
                          }) != object->end();
    }
    return false;
  }

  [[nodiscard]] boolean_type is_null() const {
    return type_ == json_class_t::null;
  }

  [[nodiscard]] boolean_type is_object() const {
    return type_ == json_class_t::object;
  }

  [[nodiscard]] boolean_type is_array() const {
    return type_ == json_class_t::array;
  }

  [[nodiscard]] boolean_type is_string() const {
    return type_ == json_class_t::string;
  }

  [[nodiscard]] boolean_type is_floating() const {
    return type_ == json_class_t::floating;
  }

  [[nodiscard]] boolean_type is_integral() const {
    return type_ == json_class_t::integral;
  }

  [[nodiscard]] boolean_type is_boolean() const {
    return type_ == json_class_t::boolean;
  }

public:
  object_type& get_data() {
    if (type_ != json_class_t::object) {
      throw std::logic_error{"Trying to access non-object types as object"};
    }
    return *std::get_if<object_type>(&data_);
  }

  [[nodiscard]] json_class_t get_type() const { return type_; }

  [[nodiscard]] string_type get_string() const {
    return is_string() ? escape_string(*std::get_if<string_type>(&data_))
                       : string_type{};
  }

  [[nodiscard]] floating_type get_floating() const {
    return is_floating() ? *std::get_if<floating_type>(&data_)
                         : floating_type{};
  }

  [[nodiscard]] integral_type get_integral() const {
    return is_integral() ? *std::get_if<integral_type>(&data_)
                         : integral_type{};
  }

  [[nodiscard]] boolean_type get_boolean() const {
    return is_boolean() && *std::get_if<boolean_type>(&data_);
  }

public:
  [[nodiscard]] string_type to_string(const boolean_type mangling = false,
                                      const size_type indent = 2) const {
    std::ostringstream oss;
    make_output(oss, mangling, indent, indent);
    return oss.str();
  }

  static json_data_t __internal_make(const json_class_t type) {
    json_data_t obj;
    obj.set_type(type);
    return obj;
  }

private:
  void make_output(std::ostringstream& oss, const boolean_type mangling,
                   const size_type base_indent, const size_type indent) const {
    const string_type indent_str(indent, get_char(ascii_t::space));

    switch (type_) {
      case json_class_t::object: {
        oss << get_char(ascii_t::left_curly_br);
        const auto data = std::get_if<object_type>(&data_);
        if (data && !data->empty()) {
          if (mangling) {
            oss << get_char(ascii_t::line_feed);
          }
          boolean_type first = true;
          for (const auto& [key, value] : *data) {
            if (!first) {
              oss << get_char(ascii_t::comma);
              if (mangling) {
                oss << get_char(ascii_t::line_feed);
              }
            }
            if (mangling) {
              oss << indent_str;
            }
            oss << fmt("{}{}{}{}{}", get_char(ascii_t::quot_mark),
                       escape_string(key), get_char(ascii_t::quot_mark),
                       get_char(ascii_t::colon), get_char(ascii_t::space));

            value->make_output(oss, mangling, base_indent,
                               indent + base_indent);
            first = false;
          }
          if (mangling) {
            oss << fmt(
                "{}{}", get_char(ascii_t::line_feed),
                string_type(indent - base_indent, get_char(ascii_t::space)));
          }
        }
        oss << get_char(ascii_t::right_curly_br);
        break;
      }
      case json_class_t::array: {
        oss << get_char(ascii_t::left_square_br);
        const auto data = std::get_if<array_type>(&data_);
        if (data && !data->empty()) {
          if (mangling) {
            oss << get_char(ascii_t::line_feed);
          }
          boolean_type first = true;
          for (const auto& item : *data) {
            if (!first) {
              oss << get_char(ascii_t::comma);
              if (mangling) {
                oss << get_char(ascii_t::line_feed);
              }
            }
            if (mangling) {
              oss << indent_str;
            }
            item->make_output(oss, mangling, base_indent, indent + base_indent);
            first = false;
          }
          if (mangling) {
            oss << fmt(
                "{}{}", get_char(ascii_t::line_feed),
                string_type(indent - base_indent, get_char(ascii_t::space)));
          }
        }
        oss << get_char(ascii_t::right_square_br);
        break;
      }
      case json_class_t::null:
        oss << get_as_string(nullptr);
        break;
      case json_class_t::string:
        oss << fmt("{}{}{}", get_char(ascii_t::quot_mark),
                   escape_string(*std::get_if<string_type>(&data_)),
                   get_char(ascii_t::quot_mark));
        break;
      case json_class_t::floating:
        oss << *std::get_if<floating_type>(&data_);
        break;
      case json_class_t::integral:
        oss << *std::get_if<integral_type>(&data_);
        break;
      case json_class_t::boolean:
        oss << (*std::get_if<boolean_type>(&data_) ? get_as_string(true)
                                                   : get_as_string(false));
        break;
    }
  }

  void set_type(const json_class_t type) {
    if (type_ != type) {
      clear_internal();
      type_ = type;
      switch (type_) {
        case json_class_t::null:
          data_ = null_type{};
          break;
        case json_class_t::object:
          data_ = object_type{};
          break;
        case json_class_t::array:
          data_ = array_type{};
          break;
        case json_class_t::string:
          data_ = string_type{};
          break;
        case json_class_t::floating:
          data_ = floating_type{};
          break;
        case json_class_t::integral:
          data_ = integral_type{};
          break;
        case json_class_t::boolean:
          data_ = boolean_type{};
          break;
      }
    }
  }

  void clear_internal() {
    switch (type_) {
      case json_class_t::object: {
        auto& object = *std::get_if<object_type>(&data_);
        for (auto& [dummy_, value] : object) {
          value.destroy();
        }
        object.clear();
        break;
      }
      case json_class_t::array: {
        auto& array = *std::get_if<array_type>(&data_);
        for (auto& item : array) {
          item.destroy();
        }
        array.clear();
        break;
      }
      case json_class_t::string:
        std::get_if<string_type>(&data_)->clear();
        break;
      default:
        type_ = json_class_t::null;
    }
  }

  static data_type copy_data(const json_data_t& other) {
    switch (other.type_) {
      case json_class_t::object: {
        auto object = object_type{};
        const auto other_object = std::get_if<object_type>(&other.data_);
        for (const auto& [key, value] : *other_object) {
          object.emplace_back(key, new json_data_t{*value});
        }
        return object;
      }
      case json_class_t::array: {
        auto array = array_type{};
        const auto other_array = std::get_if<array_type>(&other.data_);
        for (const auto& item : *other_array) {
          array.emplace_back(new json_data_t{*item});
        }
        return array;
      }
      case json_class_t::null:
        return *std::get_if<null_type>(&other.data_);
      case json_class_t::string:
        return *std::get_if<string_type>(&other.data_);
      case json_class_t::floating:
        return *std::get_if<floating_type>(&other.data_);
      case json_class_t::integral:
        return *std::get_if<integral_type>(&other.data_);
      case json_class_t::boolean:
        return *std::get_if<boolean_type>(&other.data_);
      default:
        return null_type{};
    }
  }

private:
  data_type data_{null_type{}};
  json_class_t type_{json_class_t::null};
};

__caitlyn_end_detail_namespace
__caitlyn_begin_json_namespace

static __detail::json_data_t make(const json_class_t value) {
  return __detail::json_data_t::__internal_make(value);
}

static __detail::json_data_t make_object() {
  return make(json_class_t::object);
}

static __detail::json_data_t make_array() { return make(json_class_t::array); }

template <typename... T>
static __detail::json_data_t make_array(T... args) {
  auto array = make(json_class_t::array);
  array.append(args...);
  return array;
}

static __detail::json_data_t make_null() { return make(json_class_t::null); }

static __detail::json_data_t make_string(
    const __detail::json_data_t::string_type& value) {
  return __detail::json_data_t{value};
}

static __detail::json_data_t make_floating(
    const __detail::json_data_t::floating_type value) {
  return __detail::json_data_t{value};
}

static __detail::json_data_t make_integral(
    const __detail::json_data_t::integral_type value) {
  return __detail::json_data_t{value};
}

static __detail::json_data_t make_boolean(
    const __detail::json_data_t::boolean_type value) {
  return __detail::json_data_t{value};
}

__caitlyn_end_json_namespace
__caitlyn_end_global_namespace

#endif  // CAITLYN_SER_JSON_TYPES_JSON_DATA_H_
