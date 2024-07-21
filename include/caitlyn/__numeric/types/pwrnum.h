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

#ifndef CAITLYN_NUMERIC_TYPES_PWRNUM_H_
#define CAITLYN_NUMERIC_TYPES_PWRNUM_H_

#include "caitlyn/__numeric/types/pwrint.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_NUMERIC_NAMESPACE_BEGIN

class pwrnum_t {
public:
  using sign_flag = bool;
  using size_type = size_t;

public:
  pwrnum_t() = default;

  pwrnum_t(const char* number) : pwrnum_t{basic_string_t<char>{number}} {}

  pwrnum_t(const basic_string_t<char>& number) {
    if (number.is_empty()) {
      throw std::invalid_argument{"Invalid number format"};
    }
    size_t point_pos = number.find('.');
    if (point_pos == basic_string_t<char>::npos) {
      integer_part_ = pwrint_t{number};
    } else {
      basic_string_t<char> integer_str = number.substr(0, point_pos);
      basic_string_t<char> fractional_str = number.substr(point_pos + 1);

      if (integer_str.is_empty()) {
        integer_str = "0";
      }
      if (fractional_str.is_empty()) {
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
  pwrnum_t add(const pwrnum_t& other) const {
    pwrint_t this_fractional = fractional_part_;
    pwrint_t other_fractional = other.fractional_part_;

    // Normalize fractional part lengths by adding leading zeros
    while (this_fractional.size() < other_fractional.size()) {
      this_fractional = this_fractional.multiply(pwrint_t{"10"});
    }
    while (other_fractional.size() < this_fractional.size()) {
      other_fractional = other_fractional.multiply(pwrint_t{"10"});
    }
    pwrint_t fractional_result = this_fractional.add(other_fractional);
    bool carry = false;

    // If the result of fractional addition exceeds the fractional limit, carry
    // over to integer part
    if (fractional_result.size() > this_fractional.size()) {
      carry = true;
      fractional_result = fractional_result.subtract(pwrint_t{"10"}.multiply(
          basic_string_t<char>{std::to_string(this_fractional.size())}));
    }
    pwrint_t integer_result = integer_part_.add(other.integer_part_);
    if (carry) {
      integer_result = integer_result.add(pwrint_t{"1"});
    }
    return pwrnum_t{integer_result.to_string() + "." +
                    fractional_result.to_string()};
  }

  pwrnum_t subtract(const pwrnum_t& other) const {
    pwrint_t this_fractional = fractional_part_;
    pwrint_t other_fractional = other.fractional_part_;

    // Normalize fractional part lengths by adding leading zeros
    while (this_fractional.size() < other_fractional.size()) {
      this_fractional = this_fractional.multiply(pwrint_t{"10"});
    }
    while (other_fractional.size() < this_fractional.size()) {
      other_fractional = other_fractional.multiply(pwrint_t{"10"});
    }

    bool borrow = false;
    if (this_fractional.less_than(other_fractional)) {
      borrow = true;
      this_fractional = this_fractional.add(pwrint_t{"10"}.multiply(
          basic_string_t<char>{std::to_string(this_fractional.size())}));
    }
    const pwrint_t fractional_result =
        this_fractional.subtract(other_fractional);

    pwrint_t integer_result = integer_part_.subtract(other.integer_part_);
    if (borrow) {
      integer_result = integer_result.subtract(pwrint_t{"1"});
    }
    return pwrnum_t{integer_result.to_string() + "." +
                    fractional_result.to_string()};
  }

  pwrnum_t multiply(const pwrnum_t& other) const {
    // Convert both numbers to their full string representation without the
    // decimal point
    const basic_string_t<char> this_full =
        integer_part_.to_string() + fractional_part_.to_string();
    const basic_string_t<char> other_full =
        other.integer_part_.to_string() + other.fractional_part_.to_string();

    // Count the number of digits after the decimal point in both numbers
    const size_t this_frac_size = fractional_part_.size();
    const size_t other_frac_size = other.fractional_part_.size();

    // Perform the multiplication on the full strings
    const pwrint_t result_full =
        pwrint_t{this_full}.multiply(pwrint_t{other_full});

    // The total number of fractional digits in the result
    const size_t total_frac_size = this_frac_size + other_frac_size;

    // Convert the result back to a string
    basic_string_t<char> result_str = result_full.to_string();

    // Insert the decimal point at the correct position
    if (total_frac_size >= result_str.size()) {
      result_str.insert(0, basic_string_t<char>(
                               total_frac_size - result_str.size() + 1, '0'));
    }
    result_str.insert(result_str.size() - total_frac_size, 1, '.');

    // Construct and return the pwrnum_t result
    return pwrnum_t{result_str};
  }

  pwrnum_t divide(const pwrnum_t& other) const {
    if (other.equal(pwrnum_t{"0"})) {
      throw std::invalid_argument{"Division by zero"};
    }
    // Convert both numbers to their full string representation without the
    // decimal point
    const basic_string_t<char> this_full =
        integer_part_.to_string() + fractional_part_.to_string();

    const basic_string_t<char> other_full =
        other.integer_part_.to_string() + other.fractional_part_.to_string();

    // Count the number of digits after the decimal point in both numbers
    const size_t this_frac_size = fractional_part_.size();
    const size_t other_frac_size = other.fractional_part_.size();

    // Perform the division on the full strings
    const pwrint_t result_full =
        pwrint_t{this_full}.divide(pwrint_t{other_full});

    // The total number of fractional digits in the result
    const size_t total_frac_size = this_frac_size - other_frac_size;

    // Convert the result back to a string
    basic_string_t<char> result_str = result_full.to_string();

    // Insert the decimal point at the correct position
    if (total_frac_size >= result_str.size()) {
      result_str.insert(0, basic_string_t<char>(
                               total_frac_size - result_str.size() + 1, '0'));
    }
    result_str.insert(result_str.size() - total_frac_size, 1, '.');

    // Construct and return the pwrnum_t result
    return pwrnum_t{result_str};
  }

public:
  pwrnum_t abs() const {
    pwrnum_t result = *this;
    result.is_negative_ = false;
    return result;
  }

  pwrnum_t pow(int exponent) const {
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

  pwrnum_t sqr() const { return this->multiply(*this); }

  pwrnum_t sqrt() const {
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
  size_type size() const {
    return integer_part_.size() + fractional_part_.size();
  }

  bool equal(const pwrnum_t& other) const {
    return integer_part_.equal(other.integer_part_) &&
           fractional_part_.equal(other.fractional_part_) &&
           is_negative_ == other.is_negative_;
  }

  bool less_than(const pwrnum_t& other) const {
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

  bool greater_than(const pwrnum_t& other) const {
    return !less_than(other) && !equal(other);
  }

  basic_string_t<char> to_string() const {
    basic_string_t<char> result = integer_part_.to_string();
    if (!fractional_part_.to_string().is_empty() &&
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

__CAITLYN_NUMERIC_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

inline bool operator<(const cait::numeric::pwrnum_t& lhs,
                      const cait::numeric::pwrnum_t& rhs) {
  return lhs.less_than(rhs);
}

inline bool operator>(const cait::numeric::pwrnum_t& lhs,
                      const cait::numeric::pwrnum_t& rhs) {
  return lhs.greater_than(rhs);
}

inline bool operator<=(const cait::numeric::pwrnum_t& lhs,
                       const cait::numeric::pwrnum_t& rhs) {
  return lhs.less_than(rhs) || lhs.equal(rhs);
}

inline bool operator>=(const cait::numeric::pwrnum_t& lhs,
                       const cait::numeric::pwrnum_t& rhs) {
  return lhs.greater_than(rhs) || lhs.equal(rhs);
}

inline bool operator==(const cait::numeric::pwrnum_t& lhs,
                       const cait::numeric::pwrnum_t& rhs) {
  return lhs.equal(rhs);
}

inline bool operator!=(const cait::numeric::pwrnum_t& lhs,
                       const cait::numeric::pwrnum_t& rhs) {
  return !lhs.equal(rhs);
}

inline cait::numeric::pwrnum_t operator+(const cait::numeric::pwrnum_t& lhs,
                                         const cait::numeric::pwrnum_t& rhs) {
  return lhs.add(rhs);
}

inline cait::numeric::pwrnum_t operator-(const cait::numeric::pwrnum_t& lhs,
                                         const cait::numeric::pwrnum_t& rhs) {
  return lhs.subtract(rhs);
}

inline cait::numeric::pwrnum_t operator*(const cait::numeric::pwrnum_t& lhs,
                                         const cait::numeric::pwrnum_t& rhs) {
  return lhs.multiply(rhs);
}

inline cait::numeric::pwrnum_t operator/(const cait::numeric::pwrnum_t& lhs,
                                         const cait::numeric::pwrnum_t& rhs) {
  return lhs.divide(rhs);
}

inline std::ostream& operator<<(std::ostream& os,
                                const cait::numeric::pwrnum_t& number) {
  os << number.to_string();
  return os;
}

inline cait::numeric::pwrnum_t operator""_pwrnum(const char* number,
                                                 const size_t) {
  return cait::numeric::pwrnum_t{number};
}

#endif  // CAITLYN_NUMERIC_TYPES_PWRNUM_H_