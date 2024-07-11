#ifndef CAITLYN_SER_JSON_TYPES_DATA_H_
#define CAITLYN_SER_JSON_TYPES_DATA_H_

#include <algorithm>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "caitlyn/ser/json/types/class.h"

namespace cait {
namespace json {
namespace __detail {

class data_t {
public:
  using array_type = std::deque<data_t*>;
  using object_type = std::vector<std::pair<std::string, data_t*>>;
  using string_type = std::string;
  using null_type = null_t;
  using floating_type = float64_t;
  using integral_type = int64_t;
  using boolean_type = bool_t;
  using size_type = size_t;

public:
  data_t() : type_{class_t::null} {
    new (&data_.null_value) null_type(nullptr);
  }

  data_t(const data_t& other) : type_(other.type_) { copy_union(other); }

  data_t(data_t&& other) noexcept : type_(other.type_) {
    move_union(std::move(other));
  }

  template <typename T>
  data_t(T value,
         typename std::enable_if<std::is_same<T, boolean_type>::value>::type* =
             nullptr)
      : type_{class_t::boolean} {
    new (&data_.boolean_value) boolean_type(value);
  }

  template <typename T>
  data_t(T value,
         typename std::enable_if<std::is_integral<T>::value &&
                                 !std::is_same<T, boolean_type>::value>::type* =
             nullptr)
      : type_{class_t::integral} {
    new (&data_.integral_value) integral_type(value);
  }

  template <typename T>
  data_t(T value,
         typename std::enable_if<std::is_floating_point<T>::value>::type* =
             nullptr)
      : type_{class_t::floating} {
    new (&data_.floating_value) floating_type(value);
  }

  template <typename T>
  data_t(T value,
         typename std::enable_if<
             std::is_convertible<T, string_type>::value>::type* = nullptr)
      : type_{class_t::string} {
    new (&data_.string_value) string_type(value);
  }

  ~data_t() { destroy_union(); }

public:
  data_t& operator=(const data_t& other) {
    if (this != &other) {
      destroy_union();
      type_ = other.type_;
      copy_union(other);
    }
    return *this;
  }

  data_t& operator=(data_t&& other) noexcept {
    if (this != &other) {
      destroy_union();
      type_ = other.type_;
      move_union(std::move(other));
    }
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_same<T, boolean_type>::value, data_t&>::type
  operator=(T value) {
    set_type(class_t::boolean);
    data_.boolean_value = value;
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_integral<T>::value &&
                              !std::is_same<T, boolean_type>::value,
                          data_t&>::type
  operator=(T value) {
    set_type(class_t::integral);
    data_.integral_value = value;
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_floating_point<T>::value, data_t&>::type
  operator=(T value) {
    set_type(class_t::floating);
    data_.floating_value = value;
    return *this;
  }

  template <typename T>
  typename std::enable_if<std::is_convertible<T, string_type>::value,
                          data_t&>::type
  operator=(T value) {
    set_type(class_t::string);
    data_.string_value = string_type(value);
    return *this;
  }

public:
  data_t& operator[](const string_type& key) {
    set_type(class_t::object);
    auto& object = data_.object_value;
    const auto it =
        std::find_if(object.begin(), object.end(),
                     [&key](const auto& pair) { return pair.first == key; });
    if (it == object.end()) {
      object.emplace_back(key, new data_t());
      return *object.back().second;
    }
    return *it->second;
  }

  data_t& operator[](const size_type index) {
    set_type(class_t::array);
    auto& array = data_.array_value;
    if (index >= array.size()) {
      array.resize(index + 1, nullptr);
    }
    if (!array[index]) {
      new(array[index]) data_t{};
    }
    return *array[index];
  }

public:
  data_t& at(const string_type& key) { return operator[](key); }

  __caitlyn_nodiscard const data_t& at(const string_type& key) const {
    const auto& object = data_.object_value;
    const auto it =
        std::find_if(object.begin(), object.end(),
                     [&key](const auto& pair) { return pair.first == key; });
    if (it == object.end()) {
      throw std::out_of_range("Key not found");
    }
    return *it->second;
  }

  data_t& at(const size_type index) { return operator[](index); }

  __caitlyn_nodiscard const data_t& at(const size_type index) const {
    return *data_.array_value.at(index);
  }

public:
  template <typename T>
  void append(T arg) {
    if (type_ != class_t::array) {
      set_type(class_t::array);
    }
    data_.array_value.emplace_back(new data_t{arg});
  }

  template <typename T, typename... Args>
  void append(T arg, Args... args) {
    append(arg);
    append(std::forward<Args>(args)...);
  }

public:
  __caitlyn_nodiscard size_type size() const {
    if (type_ == class_t::array) {
      return data_.array_value.size();
    }
    if (type_ == class_t::object) {
      return data_.object_value.size();
    }
    return static_cast<size_type>(-1);
  }

  __caitlyn_nodiscard size_type length() const { return size(); }

public:
  __caitlyn_nodiscard boolean_type has_member(const string_type& key) const {
    if (type_ == class_t::object) {
      const auto& object = data_.object_value;
      return std::find_if(object.begin(), object.end(),
                          [&key](const auto& pair) {
                            return pair.first == key;
                          }) != object.end();
    }
    return false;
  }

  __caitlyn_nodiscard boolean_type is_null() const {
    return type_ == class_t::null;
  }

  __caitlyn_nodiscard boolean_type is_object() const {
    return type_ == class_t::object;
  }

  __caitlyn_nodiscard boolean_type is_array() const {
    return type_ == class_t::array;
  }

  __caitlyn_nodiscard boolean_type is_string() const {
    return type_ == class_t::string;
  }

  __caitlyn_nodiscard boolean_type is_floating() const {
    return type_ == class_t::floating;
  }

  __caitlyn_nodiscard boolean_type is_integral() const {
    return type_ == class_t::integral;
  }

  __caitlyn_nodiscard boolean_type is_boolean() const {
    return type_ == class_t::boolean;
  }

public:
  object_type& get_data() {
    if (type_ != class_t::object) {
      throw std::logic_error("Trying to access non-object types as object");
    }
    return data_.object_value;
  }

  __caitlyn_nodiscard class_t get_type() const { return type_; }

  __caitlyn_nodiscard string_type get_string() const {
    return is_string() ? data_.string_value : string_type{};
  }

  __caitlyn_nodiscard floating_type get_floating() const {
    return is_floating() ? data_.floating_value : floating_type{};
  }

  __caitlyn_nodiscard integral_type get_integral() const {
    return is_integral() ? data_.integral_value : integral_type{};
  }

  __caitlyn_nodiscard boolean_type get_boolean() const {
    return is_boolean() && data_.boolean_value;
  }

public:
  __caitlyn_nodiscard string_type to_string(const boolean_type mangling = false,
                                            const size_type indent = 2) const {
    std::ostringstream oss;
    make_output(oss, mangling, indent, indent);
    return oss.str();
  }

  static data_t __internal_make(const class_t type) {
    data_t obj;
    obj.set_type(type);
    return std::move(obj);
  }

private:
  void make_output(std::ostringstream& oss, const boolean_type mangling,
                   const size_type base_indent, const size_type indent) const {
    const string_type indent_str(indent, ' ');

    switch (type_) {
      case class_t::object: {
        oss << '{';
        const auto& object = data_.object_value;
        if (!object.empty()) {
          if (mangling) {
            oss << '\n';
          }
          boolean_type first = true;
          for (const auto& [key, value] : object) {
            if (!first) {
              oss << ',';
              if (mangling) {
                oss << '\n';
              }
            }
            if (mangling) {
              oss << indent_str;
            }
            oss << '"' << key << "\": ";
            value->make_output(oss, mangling, base_indent,
                               indent + base_indent);
            first = false;
          }
          if (mangling) {
            oss << '\n';
          }
        }
        if (mangling) {
          oss << string_type(indent - base_indent, ' ');
        }
        oss << '}';
        break;
      }
      case class_t::array: {
        oss << '[';
        const auto& array = data_.array_value;
        if (!array.empty()) {
          if (mangling) {
            oss << '\n';
          }
          boolean_type first = true;
          for (const auto& value : array) {
            if (!first) {
              oss << ',';
              if (mangling) {
                oss << '\n';
              }
            }
            if (mangling) {
              oss << indent_str;
            }
            value->make_output(oss, mangling, base_indent,
                               indent + base_indent);
            first = false;
          }
          if (mangling) {
            oss << '\n';
          }
        }
        if (mangling) {
          oss << string_type(indent - base_indent, ' ');
        }
        oss << ']';
        break;
      }
      case class_t::string:
        oss << '"' << data_.string_value << '"';
        break;
      case class_t::floating:
        oss << data_.floating_value;
        break;
      case class_t::integral:
        oss << data_.integral_value;
        break;
      case class_t::boolean:
        oss << (data_.boolean_value ? "true" : "false");
        break;
      case class_t::null:
        oss << "null";
        break;
      default:
        break;
    }
  }

private:
  void set_type(class_t new_type) {
    if (type_ == new_type) {
      return;
    }
    destroy_union();
    type_ = new_type;
    switch (type_) {
      case class_t::null:
        new (&data_.null_value) null_type(nullptr);
        break;
      case class_t::object:
        new (&data_.object_value) object_type();
        break;
      case class_t::array:
        new (&data_.array_value) array_type();
        break;
      case class_t::string:
        new (&data_.string_value) string_type();
        break;
      case class_t::floating:
        new (&data_.floating_value) floating_type();
        break;
      case class_t::integral:
        new (&data_.integral_value) integral_type();
        break;
      case class_t::boolean:
        new (&data_.boolean_value) boolean_type();
        break;
      default:
        break;
    }
  }

  void destroy_union() {
    switch (type_) {
      case class_t::object:
        std::destroy_at(&data_.object_value);
        break;
      case class_t::array:
        for (const auto* ptr : data_.array_value) {
          delete ptr;
        }
        std::destroy_at(&data_.array_value);
        break;
      case class_t::string:
        std::destroy_at(&data_.string_value);
        break;
      case class_t::floating:
        std::destroy_at(&data_.floating_value);
        break;
      case class_t::integral:
        std::destroy_at(&data_.integral_value);
        break;
      case class_t::boolean:
        std::destroy_at(&data_.boolean_value);
        break;
      default:
        break;
    }
  }

  void copy_union(const data_t& other) {
    switch (other.type_) {
      case class_t::null:
        new (&data_.null_value) null_type(other.data_.null_value);
        break;
      case class_t::object:
        new (&data_.object_value) object_type(other.data_.object_value);
        break;
      case class_t::array:
        new (&data_.array_value) array_type(other.data_.array_value);
        for (auto* ptr : data_.array_value) {
          if (ptr) {
            *ptr = *other.data_.array_value[&ptr - &data_.array_value[0]];
          }
        }
        break;
      case class_t::string:
        new (&data_.string_value) string_type(other.data_.string_value);
        break;
      case class_t::floating:
        new (&data_.floating_value) floating_type(other.data_.floating_value);
        break;
      case class_t::integral:
        new (&data_.integral_value) integral_type(other.data_.integral_value);
        break;
      case class_t::boolean:
        new (&data_.boolean_value) boolean_type(other.data_.boolean_value);
        break;
      default:
        break;
    }
  }

  void move_union(data_t&& other) noexcept {
    switch (other.type_) {
      case class_t::null:
        new (&data_.null_value) null_type(other.data_.null_value);
        break;
      case class_t::object:
        new (&data_.object_value)
            object_type(std::move(other.data_.object_value));
        break;
      case class_t::array:
        new (&data_.array_value) array_type(std::move(other.data_.array_value));
        break;
      case class_t::string:
        new (&data_.string_value)
            string_type(std::move(other.data_.string_value));
        break;
      case class_t::floating:
        new (&data_.floating_value) floating_type(other.data_.floating_value);
        break;
      case class_t::integral:
        new (&data_.integral_value) integral_type(other.data_.integral_value);
        break;
      case class_t::boolean:
        new (&data_.boolean_value) boolean_type(other.data_.boolean_value);
        break;
      default:
        break;
    }
  }

private:
  union data_union {
    null_type null_value{};
    object_type object_value;
    array_type array_value;
    string_type string_value;
    floating_type floating_value;
    integral_type integral_value;
    boolean_type boolean_value;

    data_union() {}
    ~data_union() {}
  } data_;
  class_t type_;
};

}  // namespace __detail

static __detail::data_t make(const class_t value) {
  return __detail::data_t::__internal_make(value);
}

static __detail::data_t make_object() { return make(class_t::object); }

static __detail::data_t make_array() { return make(class_t::array); }

template <typename... Args>
static __detail::data_t make_array(Args... args) {
  auto array = make(class_t::array);
  array.append(std::forward<Args>(args)...);
  return array;
}

static __detail::data_t make_null() { return make(class_t::null); }

static __detail::data_t make_string(
    const __detail::data_t::string_type& value) {
  return __detail::data_t{value};
}

static __detail::data_t make_floating(
    const __detail::data_t::floating_type value) {
  return __detail::data_t{value};
}

static __detail::data_t make_integral(
    const __detail::data_t::integral_type value) {
  return __detail::data_t{value};
}

static __detail::data_t make_boolean(
    const __detail::data_t::boolean_type value) {
  return __detail::data_t{value};
}

}  // namespace json
}  // namespace cait

#endif  // CAITLYN_SER_JSON_TYPES_DATA_H_
