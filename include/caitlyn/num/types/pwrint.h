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

#ifndef CAITLYN_NUM_TYPES_PWRINT_H_
#define CAITLYN_NUM_TYPES_PWRINT_H_

#include "caitlyn/__detail.h"

namespace cait {

class pwrint_t {
public:
  using data_type = vector_t<int_t>;
  using sign_flag = bool_t;
  using size_type = size_t;

public:
  pwrint_t() = default;

  pwrint_t(const char_t* number) : pwrint_t{string_t{number}} {}

  pwrint_t(const string_t& number) {
    if (number.empty()) {
      throw std::invalid_argument{"Invalid number format"};
    }
    size_type start{};
    if (number[0] == '-') {
      is_negative_ = true;
      start = 1;
    } else {
      is_negative_ = false;
      if (number[0] == '+') {
        start = 1;
      }
    }
    for (size_type i = start; i < number.size(); ++i) {
      if (!is_digit(number[i])) {
        throw std::invalid_argument{"Invalid number format"};
      }
      digits_.push_back(number[i] - '0');
    }
    std::reverse(digits_.begin(), digits_.end());
    remove_leading_zeros();
  }

  pwrint_t(const pwrint_t& other) = default;

  pwrint_t(pwrint_t&& other) noexcept
      : digits_(std::move(other.digits_)), is_negative_(other.is_negative_) {
    other.is_negative_ = false;
  }

public:
  pwrint_t& operator=(const pwrint_t& other) {
    if (this != &other) {
      digits_ = other.digits_;
      is_negative_ = other.is_negative_;
    }
    return *this;
  }

  pwrint_t& operator=(pwrint_t&& other) noexcept {
    if (this != &other) {
      digits_ = std::move(other.digits_);
      is_negative_ = other.is_negative_;
      other.is_negative_ = false;
    }
    return *this;
  }

public:
  [[nodiscard]] pwrint_t add(const pwrint_t& other) const {
    if (is_negative_ == other.is_negative_) {
      pwrint_t result;
      result.is_negative_ = is_negative_;
      result.digits_.resize(std::max(digits_.size(), other.digits_.size()) + 1,
                            0);
      int_t carry = 0;
      for (size_type i = 0; i < result.digits_.size(); ++i) {
        int_t sum = carry;
        if (i < digits_.size()) {
          sum += digits_[i];
        }
        if (i < other.digits_.size()) {
          sum += other.digits_[i];
        }
        result.digits_[i] = sum % 10;
        carry = sum / 10;
      }
      result.remove_leading_zeros();
      return result;
    }
    pwrint_t abs_this = *this;
    abs_this.is_negative_ = false;
    pwrint_t abs_other = other;
    abs_other.is_negative_ = false;

    if (abs_this.greater_than(abs_other)) {
      return abs_this.subtract(abs_other);
    }
    pwrint_t result = abs_other.subtract(abs_this);
    result.is_negative_ = other.is_negative_;
    return result;
  }

  [[nodiscard]] pwrint_t subtract(const pwrint_t& other) const {
    if (this->is_negative_ != other.is_negative_) {
      pwrint_t result = add(other);
      result.is_negative_ = this->is_negative_;
      return result;
    }
    if (equal(other)) {
      return pwrint_t{"0"};
    }
    const bool_t result_is_negative = less_than(other);
    const pwrint_t& larger = result_is_negative ? other : *this;
    const pwrint_t& smaller = result_is_negative ? *this : other;

    pwrint_t result;
    result.is_negative_ = result_is_negative;
    result.digits_.resize(larger.digits_.size(), 0);

    int_t borrow = 0;
    for (size_type i = 0; i < larger.digits_.size(); ++i) {
      int_t diff = larger.digits_[i] - borrow;
      if (i < smaller.digits_.size()) {
        diff -= smaller.digits_[i];
      }
      if (diff < 0) {
        diff += 10;
        borrow = 1;
      } else {
        borrow = 0;
      }
      result.digits_[i] = diff;
    }
    result.remove_leading_zeros();
    return result;
  }

  [[nodiscard]] pwrint_t multiply(const pwrint_t& other) const {
    pwrint_t result;
    result.digits_.resize(digits_.size() + other.digits_.size(), 0);

    for (size_type i = 0; i < digits_.size(); ++i) {
      int_t carry = 0;
      for (size_type j = 0; j < other.digits_.size() || carry != 0; ++j) {
        const int_t sum =
            result.digits_[i + j] +
            digits_[i] * (j < other.digits_.size() ? other.digits_[j] : 0) +
            carry;
        result.digits_[i + j] = sum % 10;
        carry = sum / 10;
      }
    }
    result.is_negative_ = is_negative_ != other.is_negative_;
    result.remove_leading_zeros();
    return result;
  }

  [[nodiscard]] pwrint_t divide(const pwrint_t& other) const {
    if (other.equal(pwrint_t{"0"})) {
      throw std::invalid_argument{"Division by zero"};
    }
    pwrint_t dividend = *this;
    dividend.is_negative_ = false;
    pwrint_t divisor = other;
    divisor.is_negative_ = false;
    pwrint_t quotient{"0"};
    pwrint_t current{"0"};

    for (auto i = static_cast<ssize_t>(digits_.size() - 1); i >= 0; --i) {
      current.digits_.insert(current.digits_.begin(), digits_[i]);
      current.remove_leading_zeros();
      auto x{0};
      auto left{0};
      auto right{10};
      while (left <= right) {
        const auto mid = (left + right) / 2;
        pwrint_t tmp = divisor.multiply(pwrint_t{std::to_string(mid)});
        if (tmp.less_than(current) || tmp.equal(current)) {
          x = mid;
          left = mid + 1;
        } else {
          right = mid - 1;
        }
      }
      quotient.digits_.insert(quotient.digits_.begin(), x);
      current = current.subtract(divisor.multiply(pwrint_t{std::to_string(x)}));
    }

    quotient.is_negative_ = is_negative_ != other.is_negative_;
    quotient.remove_leading_zeros();
    return quotient;
  }

  [[nodiscard]] pwrint_t modulo(const pwrint_t& other) const {
    pwrint_t result = subtract(divide(other).multiply(other));
    if (result.is_negative_ != is_negative_) {
      result.is_negative_ = is_negative_;
    }
    return result;
  }

public:
  [[nodiscard]] pwrint_t abs() const {
    pwrint_t result = *this;
    result.is_negative_ = false;
    return result;
  }

  [[nodiscard]] pwrint_t pow(int_t exponent) const {
    if (exponent < 0) {
      throw std::invalid_argument{"Negative exponent not supported"};
    }
    pwrint_t result{"1"};
    pwrint_t base = *this;

    while (exponent > 0) {
      if (exponent % 2 == 1) {
        result = result.multiply(base);
      }
      base = base.multiply(base);
      exponent /= 2;
    }
    return result;
  }

  [[nodiscard]] pwrint_t sqr() const { return this->multiply(*this); }

  [[nodiscard]] pwrint_t sqrt() const {
    if (is_negative_) {
      throw std::invalid_argument{"Square root of negative number"};
    }
    if (this->equal(pwrint_t{"0"}) || this->equal(pwrint_t{"1"})) {
      return *this;
    }
    pwrint_t low{"1"};
    pwrint_t high = *this;
    pwrint_t squared{};

    while (low.less_than(high) || low.equal(high)) {
      pwrint_t mid = low.add(high).divide(pwrint_t{"2"});
      squared = mid.sqr();
      if (squared.equal(*this)) {
        return mid;
      }
      if (squared.less_than(*this)) {
        low = mid.add(pwrint_t{"1"});
      } else {
        high = mid.subtract(pwrint_t{"1"});
      }
    }
    return high;
  }

public:
  [[nodiscard]] size_type size() const { return digits_.size(); }

  [[nodiscard]] bool_t equal(const pwrint_t& other) const {
    return digits_ == other.digits_ && is_negative_ == other.is_negative_;
  }

  [[nodiscard]] bool_t less_than(const pwrint_t& other) const {
    if (is_negative_ != other.is_negative_) {
      return is_negative_;
    }
    if (digits_.size() != other.digits_.size()) {
      return digits_.size() < other.digits_.size();
    }
    for (size_type i = digits_.size(); i > 0; --i) {
      if (digits_[i - 1] != other.digits_[i - 1]) {
        return digits_[i - 1] < other.digits_[i - 1];
      }
    }
    return false;
  }

  [[nodiscard]] bool_t greater_than(const pwrint_t& other) const {
    return !less_than(other) && !equal(other);
  }

  [[nodiscard]] string_t to_string() const {
    if (digits_.empty()) {
      return "0";
    }
    string_t result;
    if (is_negative_) {
      result.push_back('-');
    }
    for (auto it = digits_.rbegin(); it != digits_.rend(); ++it) {
      result.push_back(static_cast<char_t>(*it + '0'));
    }
    return result;
  }

public:
  void remove_leading_zeros() {
    while (!digits_.empty() && digits_.back() == 0) {
      digits_.pop_back();
    }
    if (digits_.empty()) {
      is_negative_ = false;
    }
  }

private:
  data_type digits_;
  sign_flag is_negative_ = false;
};

}  // namespace cait

static cait::bool_t operator<(const cait::pwrint_t& lhs,
                              const cait::pwrint_t& rhs) {
  return lhs.less_than(rhs);
}

static cait::bool_t operator>(const cait::pwrint_t& lhs,
                              const cait::pwrint_t& rhs) {
  return lhs.greater_than(rhs);
}

static cait::bool_t operator<=(const cait::pwrint_t& lhs,
                               const cait::pwrint_t& rhs) {
  return lhs.less_than(rhs) || lhs.equal(rhs);
}

static cait::bool_t operator>=(const cait::pwrint_t& lhs,
                               const cait::pwrint_t& rhs) {
  return lhs.greater_than(rhs) || lhs.equal(rhs);
}

static cait::bool_t operator==(const cait::pwrint_t& lhs,
                               const cait::pwrint_t& rhs) {
  return lhs.equal(rhs);
}

static cait::bool_t operator!=(const cait::pwrint_t& lhs,
                               const cait::pwrint_t& rhs) {
  return !lhs.equal(rhs);
}

static cait::pwrint_t operator+(const cait::pwrint_t& lhs,
                                const cait::pwrint_t& rhs) {
  return lhs.add(rhs);
}

static cait::pwrint_t operator-(const cait::pwrint_t& lhs,
                                const cait::pwrint_t& rhs) {
  return lhs.subtract(rhs);
}

static cait::pwrint_t operator*(const cait::pwrint_t& lhs,
                                const cait::pwrint_t& rhs) {
  return lhs.multiply(rhs);
}

static cait::pwrint_t operator/(const cait::pwrint_t& lhs,
                                const cait::pwrint_t& rhs) {
  return lhs.divide(rhs);
}

static cait::pwrint_t operator%(const cait::pwrint_t& lhs,
                                const cait::pwrint_t& rhs) {
  return lhs.modulo(rhs);
}

static cait::ostream_t& operator<<(cait::ostream_t& os,
                                   const cait::pwrint_t& number) {
  os << number.to_string();
  return os;
}

static cait::pwrint_t operator""_pwrint(const cait::char_t* number,
                                        const cait::size_t) {
  return cait::pwrint_t{number};
}

#endif  // CAITLYN_NUM_TYPES_PWRINT_H_
