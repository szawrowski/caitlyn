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

#ifndef CAITLYN_NUMERIC_TYPES_BIGFLOAT_H_
#define CAITLYN_NUMERIC_TYPES_BIGFLOAT_H_

#include "Caitlyn/__Numeric/Types/BigInteger.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class BigFloat
{
public:
    using SignFlag = BigInteger::SignFlag;

public:
    BigFloat() = default;

    BigFloat(const double value) : BigFloat{std::to_string(value)}
    {
    }

    BigFloat(const char* number) : BigFloat{String{number}}
    {
    }

    BigFloat(const String& number)
    {
        if (number.IsEmpty())
        {
            throw std::invalid_argument{"Invalid number format"};
        }
        size_t point_pos = number.Find(def::FullStop);
        if (point_pos == String::NPosition)
        {
            integerPart_ = BigInteger{number};
        }
        else
        {
            String integer_str = number.Substring(0, point_pos);
            String fractional_str = number.Substring(point_pos + 1);

            if (integer_str.IsEmpty())
            {
                integer_str = def::DigitZero;
            }
            if (fractional_str.IsEmpty())
            {
                fractional_str = def::DigitZero;
            }
            integerPart_ = BigInteger{integer_str};
            fractionalPart_ = BigInteger{fractional_str};
        }
    }

    BigFloat(const BigFloat& other) = default;

    BigFloat(BigFloat&& other) noexcept
        : integerPart_(std::move(other.integerPart_)),
          fractionalPart_(std::move(other.fractionalPart_)),
          isNegative_(other.isNegative_)
    {
        other.isNegative_ = false;
    }

public:
    BigFloat& operator=(const BigFloat& other)
    {
        if (this != &other)
        {
            integerPart_ = other.integerPart_;
            fractionalPart_ = other.fractionalPart_;
            isNegative_ = other.isNegative_;
        }
        return *this;
    }

    BigFloat& operator=(BigFloat&& other) noexcept
    {
        if (this != &other)
        {
            integerPart_ = std::move(other.integerPart_);
            fractionalPart_ = std::move(other.fractionalPart_);
            isNegative_ = other.isNegative_;
            other.isNegative_ = false;
        }
        return *this;
    }

public:
    BigFloat Add(const BigFloat& other) const
    {
        BigInteger this_fractional = fractionalPart_;
        BigInteger other_fractional = other.fractionalPart_;

        // Normalize fractional part lengths by adding leading zeros
        while (this_fractional.Size() < other_fractional.Size())
        {
            this_fractional = this_fractional.Multiply(BigInteger{"10"});
        }
        while (other_fractional.Size() < this_fractional.Size())
        {
            other_fractional = other_fractional.Multiply(BigInteger{"10"});
        }
        BigInteger fractional_result = this_fractional.Add(other_fractional);
        bool carry = false;

        // If the result of fractional addition exceeds the fractional limit, carry
        // over to integer part
        if (fractional_result.Size() > this_fractional.Size())
        {
            carry = true;
            fractional_result = fractional_result.Subtract(BigInteger{"10"}.Multiply(this_fractional.Size()));
        }
        BigInteger integer_result = integerPart_.Add(other.integerPart_);
        if (carry)
        {
            integer_result = integer_result.Add(BigInteger{def::DigitOne});
        }
        return BigFloat{integer_result.ToString() + def::FullStop + fractional_result.ToString()};
    }

    BigFloat Subtract(const BigFloat& other) const
    {
        BigInteger this_fractional = fractionalPart_;
        BigInteger other_fractional = other.fractionalPart_;

        // Normalize fractional part lengths by adding leading zeros
        while (this_fractional.Size() < other_fractional.Size())
        {
            this_fractional = this_fractional.Multiply(BigInteger{"10"});
        }
        while (other_fractional.Size() < this_fractional.Size())
        {
            other_fractional = other_fractional.Multiply(BigInteger{"10"});
        }

        bool borrow = false;
        if (this_fractional.LessThan(other_fractional))
        {
            borrow = true;
            this_fractional = this_fractional.Add(BigInteger{"10"}.Multiply(this_fractional.Size()));
        }
        const BigInteger fractional_result = this_fractional.Subtract(other_fractional);

        BigInteger integer_result = integerPart_.Subtract(other.integerPart_);
        if (borrow)
        {
            integer_result = integer_result.Subtract(BigInteger{"1"});
        }
        return BigFloat{integer_result.ToString() + "." + fractional_result.ToString()};
    }

    BigFloat Multiply(const BigFloat& other) const
    {
        // Convert both numbers to their full string representation without the
        // decimal point
        const String this_full = integerPart_.ToString() + fractionalPart_.ToString();
        const String other_full = other.integerPart_.ToString() + other.fractionalPart_.ToString();

        // Count the number of digits after the decimal point in both numbers
        const size_t this_frac_size = fractionalPart_.Size();
        const size_t other_frac_size = other.fractionalPart_.Size();

        // Perform the multiplication on the full strings
        const BigInteger result_full = BigInteger{this_full}.Multiply(BigInteger{other_full});

        // The total number of fractional digits in the result
        const size_t total_frac_size = this_frac_size + other_frac_size;

        // Convert the result back to a string
        String result_str = result_full.ToString();

        // Insert the decimal point at the correct position
        if (total_frac_size >= result_str.size())
        {
            result_str.Insert(0, String(total_frac_size - result_str.size() + 1, '0'));
        }
        result_str.Insert(result_str.size() - total_frac_size, 1, '.');

        // Construct and return the BigFloat result
        return BigFloat{result_str};
    }

    BigFloat Divide(const BigFloat& other) const
    {
        if (other.Equal(BigFloat{"0"}))
        {
            throw std::invalid_argument{"Division by zero"};
        }
        // Convert both numbers to their full string representation without the
        // decimal point
        const String this_full = integerPart_.ToString() + fractionalPart_.ToString();

        const String other_full = other.integerPart_.ToString() + other.fractionalPart_.ToString();

        // Count the number of digits after the decimal point in both numbers
        const size_t this_frac_size = fractionalPart_.Size();
        const size_t other_frac_size = other.fractionalPart_.Size();

        // Perform the division on the full strings
        const BigInteger result_full = BigInteger{this_full}.Divide(BigInteger{other_full});

        // The total number of fractional digits in the result
        const size_t total_frac_size = this_frac_size - other_frac_size;

        // Convert the result back to a string
        String result_str = result_full.ToString();

        // Insert the decimal point at the correct position
        if (total_frac_size >= result_str.size())
        {
            result_str.Insert(0, String(total_frac_size - result_str.size() + 1, '0'));
        }
        result_str.Insert(result_str.size() - total_frac_size, 1, '.');

        // Construct and return the BigFloat result
        return BigFloat{result_str};
    }

public:
    BigFloat Abs() const
    {
        BigFloat result = *this;
        result.isNegative_ = false;
        return result;
    }

    BigFloat Pow(int exponent) const
    {
        if (exponent < 0)
        {
            throw std::invalid_argument{"Negative exponent not supported"};
        }
        BigFloat result{"1"};
        BigFloat base = *this;

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

    BigFloat Sqr() const
    {
        return this->Multiply(*this);
    }

    BigFloat Sqrt() const
    {
        if (isNegative_)
        {
            throw std::invalid_argument{"Square root of negative number"};
        }
        if (this->Equal(BigFloat{"0"}) || this->Equal(BigFloat{"1"}))
        {
            return *this;
        }
        BigFloat low{"1"};
        BigFloat high = *this;
        BigFloat squared{};

        while (low.LessThan(high) || low.Equal(high))
        {
            BigFloat mid = low.Add(high).Divide(BigFloat{"2"});
            squared = mid.Sqr();
            if (squared.Equal(*this))
            {
                return mid;
            }
            if (squared.LessThan(*this))
            {
                low = mid.Add(BigFloat{"1"});
            }
            else
            {
                high = mid.Subtract(BigFloat{"1"});
            }
        }
        return high;
    }

public:
    SizeType Size() const
    {
        return integerPart_.Size() + fractionalPart_.Size();
    }

    bool Equal(const BigFloat& other) const
    {
        return integerPart_.Equal(other.integerPart_) && fractionalPart_.Equal(other.fractionalPart_) &&
               isNegative_ == other.isNegative_;
    }

    bool LessThan(const BigFloat& other) const
    {
        if (isNegative_ != other.isNegative_)
        {
            return isNegative_;
        }
        if (integerPart_.LessThan(other.integerPart_))
        {
            return true;
        }
        if (integerPart_.GreaterThan(other.integerPart_))
        {
            return false;
        }
        return fractionalPart_.LessThan(other.fractionalPart_);
    }

    bool GreaterThan(const BigFloat& other) const
    {
        return !LessThan(other) && !Equal(other);
    }

    String ToString() const
    {
        String result = integerPart_.ToString();
        if (!fractionalPart_.ToString().IsEmpty() && fractionalPart_.ToString() != "0")
        {
            result.PushBack('.');
            result += fractionalPart_.ToString();
        }
        return result;
    }

private:
    void RemoveLeadingZeros()
    {
        integerPart_.RemoveLeadingZeros();
        fractionalPart_.RemoveLeadingZeros();
    }

private:
    BigInteger integerPart_;
    BigInteger fractionalPart_;
    SignFlag isNegative_ = false;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline bool operator<(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.LessThan(rhs);
}

inline bool operator>(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.GreaterThan(rhs);
}

inline bool operator<=(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.LessThan(rhs) || lhs.Equal(rhs);
}

inline bool operator>=(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.GreaterThan(rhs) || lhs.Equal(rhs);
}

inline bool operator==(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.Equal(rhs);
}

inline bool operator!=(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return !lhs.Equal(rhs);
}

inline cait::BigFloat operator+(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.Add(rhs);
}

inline cait::BigFloat operator-(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.Subtract(rhs);
}

inline cait::BigFloat operator*(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.Multiply(rhs);
}

inline cait::BigFloat operator/(const cait::BigFloat& lhs, const cait::BigFloat& rhs)
{
    return lhs.Divide(rhs);
}

inline std::ostream& operator<<(std::ostream& os, const cait::BigFloat& number)
{
    os << number.ToString();
    return os;
}

inline cait::BigFloat operator""_bigfloat(const char* number, const size_t)
{
    return cait::BigFloat{number};
}

#endif // CAITLYN_NUMERIC_TYPES_BIGFLOAT_H_
