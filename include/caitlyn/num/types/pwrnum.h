// Copyright (c) 2024, Alexander Szawrowski
//
// This file is distributed under the MIT License.
// See LICENSE file for details.

#ifndef CAITLYN_NUM_TYPES_PWRNUM_H_
#define CAITLYN_NUM_TYPES_PWRNUM_H_

#include "caitlyn/num/types/pwrint.h"

BEGIN_CAITLYN_NS

class pwrnum_t {
public:
  using sign_flag = bool_t;
  using size_type = size_t;

public:
  pwrnum_t() = default;

  pwrnum_t(const char_t* number) : pwrnum_t{string_t{number}} {}

  pwrnum_t(const string_t& number) {
    if (number.empty()) {
      throw std::invalid_argument{"Invalid number format"};
    }
    size_t point_pos = number.find('.');
    if (point_pos == string_t::npos) {
      integer_part_ = pwrint_t{number};
    } else {
      string_t integer_str = number.substr(0, point_pos);
      string_t fractional_str = number.substr(point_pos + 1);

      if (integer_str.empty()) {
        integer_str = "0";
      }
      if (fractional_str.empty()) {
        fractional_str = "0";
      }

      integer_part_ = pwrint_t{integer_str};
      fractional_part_ = pwrint_t{fractional_str};
    }
  }

  pwrnum_t(const pwrnum_t& other) = default;

  pwrnum_t(pwrnum_t&& other) noexcept
      : integer_part_(std::move(other.integer_part_)),
        fractional_part_(std::move(other.fractional_part_)),
        is_negative_(other.is_negative_) {
    other.is_negative_ = false;
  }

public:
  pwrnum_t& operator=(const pwrnum_t& other) {
    if (this != &other) {
      integer_part_ = other.integer_part_;
      fractional_part_ = other.fractional_part_;
      is_negative_ = other.is_negative_;
    }
    return *this;
  }

  pwrnum_t& operator=(pwrnum_t&& other) noexcept {
    if (this != &other) {
      integer_part_ = std::move(other.integer_part_);
      fractional_part_ = std::move(other.fractional_part_);
      is_negative_ = other.is_negative_;
      other.is_negative_ = false;
    }
    return *this;
  }

public:
  [[nodiscard]] pwrnum_t add(const pwrnum_t& other) const {
    pwrnum_t result;
    result.integer_part_ = integer_part_.add(other.integer_part_);
    result.fractional_part_ = fractional_part_.add(other.fractional_part_);
    result.remove_leading_zeros();
    return result;
  }

  [[nodiscard]] pwrnum_t subtract(const pwrnum_t& other) const {
    pwrnum_t result;
    result.integer_part_ = integer_part_.subtract(other.integer_part_);
    result.fractional_part_ = fractional_part_.subtract(other.fractional_part_);
    result.remove_leading_zeros();
    return result;
  }

  [[nodiscard]] pwrnum_t multiply(const pwrnum_t& other) const {
    pwrnum_t result;
    result.integer_part_ = integer_part_.multiply(other.integer_part_);
    result.fractional_part_ = fractional_part_.multiply(other.fractional_part_);
    result.remove_leading_zeros();
    return result;
  }

  [[nodiscard]] pwrnum_t divide(const pwrnum_t& other) const {
    if (other.equal(pwrnum_t{"0"})) {
      throw std::invalid_argument{"Division by zero"};
    }
    pwrnum_t result;
    result.integer_part_ = integer_part_.divide(other.integer_part_);
    result.fractional_part_ = fractional_part_.divide(other.fractional_part_);
    result.remove_leading_zeros();
    return result;
  }

public:
  [[nodiscard]] pwrnum_t abs() const {
    pwrnum_t result = *this;
    result.is_negative_ = false;
    return result;
  }

  [[nodiscard]] pwrnum_t pow(int_t exponent) const {
    if (exponent < 0) {
      throw std::invalid_argument{"Negative exponent not supported"};
    }
    pwrnum_t result{"1"};
    pwrnum_t base = *this;

    while (exponent > 0) {
      if (exponent % 2 == 1) {
        result = result.multiply(base);
      }
      base = base.multiply(base);
      exponent /= 2;
    }
    return result;
  }

  [[nodiscard]] pwrnum_t sqr() const { return this->multiply(*this); }

  [[nodiscard]] pwrnum_t sqrt() const {
    if (is_negative_) {
      throw std::invalid_argument{"Square root of negative number"};
    }
    if (this->equal(pwrnum_t{"0"}) || this->equal(pwrnum_t{"1"})) {
      return *this;
    }
    pwrnum_t low{"1"};
    pwrnum_t high = *this;
    pwrnum_t squared{};

    while (low.less_than(high) || low.equal(high)) {
      pwrnum_t mid = low.add(high).divide(pwrnum_t{"2"});
      squared = mid.sqr();
      if (squared.equal(*this)) {
        return mid;
      }
      if (squared.less_than(*this)) {
        low = mid.add(pwrnum_t{"1"});
      } else {
        high = mid.subtract(pwrnum_t{"1"});
      }
    }
    return high;
  }

public:
  [[nodiscard]] size_type size() const {
    return integer_part_.size() + fractional_part_.size();
  }

  [[nodiscard]] bool_t equal(const pwrnum_t& other) const {
    return integer_part_.equal(other.integer_part_) &&
           fractional_part_.equal(other.fractional_part_) &&
           is_negative_ == other.is_negative_;
  }

  [[nodiscard]] bool_t less_than(const pwrnum_t& other) const {
    if (is_negative_ != other.is_negative_) {
      return is_negative_;
    }
    if (integer_part_.less_than(other.integer_part_)) {
      return true;
    }
    if (integer_part_.greater_than(other.integer_part_)) {
      return false;
    }
    return fractional_part_.less_than(other.fractional_part_);
  }

  [[nodiscard]] bool_t greater_than(const pwrnum_t& other) const {
    return !less_than(other) && !equal(other);
  }

  [[nodiscard]] string_t to_string() const {
    string_t result = integer_part_.to_string();
    if (!fractional_part_.to_string().empty() &&
        fractional_part_.to_string() != "0") {
      result.push_back('.');
      result += fractional_part_.to_string();
    }
    return result;
  }

private:
  void remove_leading_zeros() {
    integer_part_.remove_leading_zeros();
    fractional_part_.remove_leading_zeros();
  }

private:
  pwrint_t integer_part_;
  pwrint_t fractional_part_;
  sign_flag is_negative_ = false;
};

END_CAITLYN_NS

static cait::bool_t operator<(const cait::pwrnum_t& lhs,
                              const cait::pwrnum_t& rhs) {
  return lhs.less_than(rhs);
}

static cait::bool_t operator>(const cait::pwrnum_t& lhs,
                              const cait::pwrnum_t& rhs) {
  return lhs.greater_than(rhs);
}

static cait::bool_t operator<=(const cait::pwrnum_t& lhs,
                               const cait::pwrnum_t& rhs) {
  return lhs.less_than(rhs) || lhs.equal(rhs);
}

static cait::bool_t operator>=(const cait::pwrnum_t& lhs,
                               const cait::pwrnum_t& rhs) {
  return lhs.greater_than(rhs) || lhs.equal(rhs);
}

static cait::bool_t operator==(const cait::pwrnum_t& lhs,
                               const cait::pwrnum_t& rhs) {
  return lhs.equal(rhs);
}

static cait::bool_t operator!=(const cait::pwrnum_t& lhs,
                               const cait::pwrnum_t& rhs) {
  return !lhs.equal(rhs);
}

static cait::pwrnum_t operator+(const cait::pwrnum_t& lhs,
                                const cait::pwrnum_t& rhs) {
  return lhs.add(rhs);
}

static cait::pwrnum_t operator-(const cait::pwrnum_t& lhs,
                                const cait::pwrnum_t& rhs) {
  return lhs.subtract(rhs);
}

static cait::pwrnum_t operator*(const cait::pwrnum_t& lhs,
                                const cait::pwrnum_t& rhs) {
  return lhs.multiply(rhs);
}

static cait::pwrnum_t operator/(const cait::pwrnum_t& lhs,
                                const cait::pwrnum_t& rhs) {
  return lhs.divide(rhs);
}

static cait::ostream_t& operator<<(cait::ostream_t& os,
                                   const cait::pwrnum_t& number) {
  os << number.to_string();
  return os;
}

static cait::pwrnum_t operator""_pwrnum(const cait::char_t* number,
                                        const cait::size_t) {
  return cait::pwrnum_t{number};
}

#endif  // CAITLYN_NUM_TYPES_PWRNUM_H_
