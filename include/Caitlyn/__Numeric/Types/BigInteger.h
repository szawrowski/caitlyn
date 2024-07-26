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

#ifndef CAITLYN_NUMERIC_TYPES_BIGINTEGER_H_
#define CAITLYN_NUMERIC_TYPES_BIGINTEGER_H_

#include <algorithm>
#include <stdexcept>
#include <string>
#include <vector>

#include "Caitlyn/__Core/String.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class BigInteger
{
public:
    using DataType = std::vector<Int>;
    using SignFlag = Bool;

public:
    BigInteger() = default;

    BigInteger(const int64_t value) : BigInteger{std::to_string(value)}
    {
    }

    BigInteger(const uint64_t value) : BigInteger{std::to_string(value)}
    {
    }

    BigInteger(CString number) : BigInteger{String{number}}
    {
    }

    BigInteger(const String& number)
    {
        if (number.IsEmpty())
        {
            throw std::invalid_argument{"Invalid number format"};
        }
        SizeType start{};
        if (number[0] == '-')
        {
            is_negative_ = true;
            start = 1;
        }
        else
        {
            is_negative_ = false;
            if (number[0] == '+')
            {
                start = 1;
            }
        }
        for (SizeType i = start; i < number.size(); ++i)
        {
            if (!IsDigit(number[i].GetCodePoint()))
            {
                throw std::invalid_argument{"Invalid number format"};
            }
            digits_.push_back(static_cast<int>(number[i].GetCodePoint() - 0x30));
        }
        std::reverse(digits_.begin(), digits_.end());
        RemoveLeadingZeros();
    }

    BigInteger(const BigInteger& other) = default;

    BigInteger(BigInteger&& other) noexcept : digits_(std::move(other.digits_)), is_negative_(other.is_negative_)
    {
        other.is_negative_ = false;
    }

public:
    BigInteger& operator=(const BigInteger& other)
    {
        if (this != &other)
        {
            digits_ = other.digits_;
            is_negative_ = other.is_negative_;
        }
        return *this;
    }

    BigInteger& operator=(BigInteger&& other) noexcept
    {
        if (this != &other)
        {
            digits_ = std::move(other.digits_);
            is_negative_ = other.is_negative_;
            other.is_negative_ = false;
        }
        return *this;
    }

public:
    BigInteger Add(const BigInteger& other) const
    {
        if (is_negative_ == other.is_negative_)
        {
            BigInteger result;
            result.is_negative_ = is_negative_;
            result.digits_.resize(std::max(digits_.size(), other.digits_.size()) + 1, 0);
            int carry = 0;
            for (SizeType i = 0; i < result.digits_.size(); ++i)
            {
                int sum = carry;
                if (i < digits_.size())
                {
                    sum += digits_[i];
                }
                if (i < other.digits_.size())
                {
                    sum += other.digits_[i];
                }
                result.digits_[i] = sum % 10;
                carry = sum / 10;
            }
            result.RemoveLeadingZeros();
            return result;
        }
        BigInteger abs_this = *this;
        abs_this.is_negative_ = false;
        BigInteger abs_other = other;
        abs_other.is_negative_ = false;

        if (abs_this.GreaterThan(abs_other))
        {
            return abs_this.Subtract(abs_other);
        }
        BigInteger result = abs_other.Subtract(abs_this);
        result.is_negative_ = other.is_negative_;
        return result;
    }

    BigInteger Subtract(const BigInteger& other) const
    {
        if (this->is_negative_ != other.is_negative_)
        {
            BigInteger result = Add(other);
            result.is_negative_ = this->is_negative_;
            return result;
        }
        if (Equal(other))
        {
            return BigInteger{"0"};
        }
        const bool result_is_negative = LessThan(other);
        const BigInteger& larger = result_is_negative ? other : *this;
        const BigInteger& smaller = result_is_negative ? *this : other;

        BigInteger result;
        result.is_negative_ = result_is_negative;
        result.digits_.resize(larger.digits_.size(), 0);

        int borrow = 0;
        for (SizeType i = 0; i < larger.digits_.size(); ++i)
        {
            int diff = larger.digits_[i] - borrow;
            if (i < smaller.digits_.size())
            {
                diff -= smaller.digits_[i];
            }
            if (diff < 0)
            {
                diff += 10;
                borrow = 1;
            }
            else
            {
                borrow = 0;
            }
            result.digits_[i] = diff;
        }
        result.RemoveLeadingZeros();
        return result;
    }

    BigInteger Multiply(const BigInteger& other) const
    {
        BigInteger result;
        result.digits_.resize(digits_.size() + other.digits_.size(), 0);

        for (SizeType i = 0; i < digits_.size(); ++i)
        {
            int carry = 0;
            for (SizeType j = 0; j < other.digits_.size() || carry != 0; ++j)
            {
                const int sum =
                    result.digits_[i + j] + digits_[i] * (j < other.digits_.size() ? other.digits_[j] : 0) + carry;
                result.digits_[i + j] = sum % 10;
                carry = sum / 10;
            }
        }
        result.is_negative_ = is_negative_ != other.is_negative_;
        result.RemoveLeadingZeros();
        return result;
    }

    BigInteger Divide(const BigInteger& other) const
    {
        if (other.Equal(BigInteger{"0"}))
        {
            throw std::invalid_argument{"Division by zero"};
        }
        BigInteger dividend = *this;
        dividend.is_negative_ = false;
        BigInteger divisor = other;
        divisor.is_negative_ = false;
        BigInteger quotient{"0"};
        BigInteger current{"0"};

        for (auto i = static_cast<SSizeType>(digits_.size() - 1); i >= 0; --i)
        {
            current.digits_.insert(current.digits_.begin(), digits_[i]);
            current.RemoveLeadingZeros();
            auto x{0};
            auto left{0};
            auto right{10};
            while (left <= right)
            {
                const auto mid = (left + right) / 2;
                BigInteger tmp = divisor.Multiply(BigInteger{std::to_string(mid)});
                if (tmp.LessThan(current) || tmp.Equal(current))
                {
                    x = mid;
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
            quotient.digits_.insert(quotient.digits_.begin(), x);
            current = current.Subtract(divisor.Multiply(BigInteger{std::to_string(x)}));
        }

        quotient.is_negative_ = is_negative_ != other.is_negative_;
        quotient.RemoveLeadingZeros();
        return quotient;
    }

    BigInteger Modulo(const BigInteger& other) const
    {
        BigInteger result = Subtract(Divide(other).Multiply(other));
        if (result.is_negative_ != is_negative_)
        {
            result.is_negative_ = is_negative_;
        }
        return result;
    }

public:
    BigInteger Abs() const
    {
        BigInteger result = *this;
        result.is_negative_ = false;
        return result;
    }

    BigInteger Pow(int exponent) const
    {
        if (exponent < 0)
        {
            throw std::invalid_argument{"Negative exponent not supported"};
        }
        BigInteger result{"1"};
        BigInteger base = *this;

        while (exponent > 0)
        {
            if (exponent % 2 == 1)
            {
                result = result.Multiply(base);
            }
            base = base.Multiply(base);
            exponent /= 2;
        }
        return result;
    }

    BigInteger Sqr() const
    {
        return this->Multiply(*this);
    }

    BigInteger Sqrt() const
    {
        if (is_negative_)
        {
            throw std::invalid_argument{"Square root of negative number"};
        }
        if (this->Equal(BigInteger{"0"}) || this->Equal(BigInteger{"1"}))
        {
            return *this;
        }
        BigInteger low{"1"};
        BigInteger high = *this;
        BigInteger squared{};

        while (low.LessThan(high) || low.Equal(high))
        {
            BigInteger mid = low.Add(high).Divide(BigInteger{"2"});
            squared = mid.Sqr();
            if (squared.Equal(*this))
            {
                return mid;
            }
            if (squared.LessThan(*this))
            {
                low = mid.Add(BigInteger{"1"});
            }
            else
            {
                high = mid.Subtract(BigInteger{"1"});
            }
        }
        return high;
    }

public:
    SizeType Size() const
    {
        return digits_.size();
    }

    bool Equal(const BigInteger& other) const
    {
        return digits_ == other.digits_ && is_negative_ == other.is_negative_;
    }

    bool LessThan(const BigInteger& other) const
    {
        if (is_negative_ != other.is_negative_)
        {
            return is_negative_;
        }
        if (digits_.size() != other.digits_.size())
        {
            return digits_.size() < other.digits_.size();
        }
        for (SizeType i = digits_.size(); i > 0; --i)
        {
            if (digits_[i - 1] != other.digits_[i - 1])
            {
                return digits_[i - 1] < other.digits_[i - 1];
            }
        }
        return false;
    }

    bool GreaterThan(const BigInteger& other) const
    {
        return !LessThan(other) && !Equal(other);
    }

    String ToString() const
    {
        if (digits_.empty())
        {
            return Def::DigitZero;
        }
        String result;
        if (is_negative_)
        {
            result.PushBack('-');
        }
        for (auto it = digits_.rbegin(); it != digits_.rend(); ++it)
        {
            result.PushBack(static_cast<char>(*it + '0'));
        }
        return result;
    }

public:
    void RemoveLeadingZeros()
    {
        while (!digits_.empty() && digits_.back() == 0)
        {
            digits_.pop_back();
        }
        if (digits_.empty())
        {
            is_negative_ = false;
        }
    }

private:
    DataType digits_;
    SignFlag is_negative_ = false;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline bool operator<(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.LessThan(rhs);
}

inline bool operator>(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.GreaterThan(rhs);
}

inline bool operator<=(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.LessThan(rhs) || lhs.Equal(rhs);
}

inline bool operator>=(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.GreaterThan(rhs) || lhs.Equal(rhs);
}

inline bool operator==(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Equal(rhs);
}

inline bool operator!=(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return !lhs.Equal(rhs);
}

inline Caitlyn::BigInteger operator+(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Add(rhs);
}

inline Caitlyn::BigInteger operator-(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Subtract(rhs);
}

inline Caitlyn::BigInteger operator*(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Multiply(rhs);
}

inline Caitlyn::BigInteger operator/(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Divide(rhs);
}

inline Caitlyn::BigInteger operator%(const Caitlyn::BigInteger& lhs, const Caitlyn::BigInteger& rhs)
{
    return lhs.Modulo(rhs);
}

inline std::ostream& operator<<(std::ostream& os, const Caitlyn::BigInteger& number)
{
    os << number.ToString();
    return os;
}

inline Caitlyn::BigInteger operator""_bigint(const char* number, const size_t)
{
    return Caitlyn::BigInteger{number};
}

#endif // CAITLYN_NUMERIC_TYPES_BIGINTEGER_H_
