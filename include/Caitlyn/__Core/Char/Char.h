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

#ifndef CAITLYN_CORE_CHAR_CHAR_H_
#define CAITLYN_CORE_CHAR_CHAR_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class Char
{
public:
    using ValueType = char;
    using DataType = std::basic_string<ValueType>;

public:
    Char() = default;

    Char(const StdChar byte)
    {
        data_ = byte;
    }

    Char(const CodePoint codePoint) : data_{FromCodePoint(codePoint)}
    {
    }

    Char(CString bytes)
    {
        if (!IsValidUtf8Char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
    }

    Char(const DataType& bytes)
    {
        if (!IsValidUtf8Char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
    }

public:
    Char& operator=(const char byte)
    {
        data_ = byte;
        return *this;
    }

    Char& operator=(const CodePoint codePoint)
    {
        data_ = FromCodePoint(codePoint);
        return *this;
    }

    Char& operator=(CString bytes)
    {
        if (!IsValidUtf8Char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
        return *this;
    }

    Char& operator=(const DataType& bytes)
    {
        if (!IsValidUtf8Char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
        return *this;
    }

    SizeType size() const
    {
        return data_.size();
    }

    SizeType Length() const
    {
        return data_.size();
    }

    CString data() const
    {
        return data_.data();
    }

    CString c_str() const
    {
        return data_.c_str();
    }

    DataType str() const
    {
        return data_;
    }

    bool IsEmpty() const
    {
        return data_.empty();
    }

    bool NotEmpty() const
    {
        return !data_.empty();
    }

    bool operator>(const Char& other) const
    {
        return data_ > other.data_;
    }

    bool operator<(const Char& other) const
    {
        return data_ < other.data_;
    }

    bool operator>=(const Char& other) const
    {
        return data_ >= other.data_;
    }

    bool operator<=(const Char& other) const
    {
        return data_ <= other.data_;
    }

    bool operator==(const Char& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const Char& other) const
    {
        return !(*this == other);
    }

public:
    CodePoint GetCodePoint() const
    {
        CodePoint codePoint;
        const auto lead = static_cast<unsigned char>(data_[0]);

        if ((lead & 0x80) == 0)
        {
            codePoint = lead;
        }
        else if ((lead & 0xE0) == 0xC0)
        {
            codePoint = (lead & 0x1F) << 6;
            codePoint |= (static_cast<unsigned char>(data_[1]) & 0x3F);
        }
        else if ((lead & 0xF0) == 0xE0)
        {
            codePoint = (lead & 0x0F) << 12;
            codePoint |= (static_cast<unsigned char>(data_[1]) & 0x3F) << 6;
            codePoint |= (static_cast<unsigned char>(data_[2]) & 0x3F);
        }
        else if ((lead & 0xF8) == 0xF0)
        {
            codePoint = (lead & 0x07) << 18;
            codePoint |= (static_cast<unsigned char>(data_[1]) & 0x3F) << 12;
            codePoint |= (static_cast<unsigned char>(data_[2]) & 0x3F) << 6;
            codePoint |= (static_cast<unsigned char>(data_[3]) & 0x3F);
        }
        else
        {
            codePoint = 0;
        }
        return codePoint;
    }

private:
    static DataType FromCodePoint(const CodePoint codePoint)
    {
        if (codePoint == 0x00)
        {
            return {};
        }
        const SizeType length = CalculateLength(codePoint);

        if (length == 1)
        {
            return DataType{static_cast<char>(codePoint)};
        }
        std::ostringstream oss;

        if (length == 2)
        {
            oss << static_cast<unsigned char>(0xC0 | (codePoint >> 6));
            oss << static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
            return oss.str();
        }
        if (length == 3)
        {
            oss << static_cast<unsigned char>(0xE0 | (codePoint >> 12));
            oss << static_cast<unsigned char>(0x80 | ((codePoint >> 6) & 0x3F));
            oss << static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
            return oss.str();
        }
        oss << static_cast<unsigned char>(0xF0 | (codePoint >> 18));
        oss << static_cast<unsigned char>(0x80 | ((codePoint >> 12) & 0x3F));
        oss << static_cast<unsigned char>(0x80 | ((codePoint >> 6) & 0x3F));
        oss << static_cast<unsigned char>(0x80 | (codePoint & 0x3F));
        return oss.str();
    }

    static SizeType CalculateLength(const CodePoint codePoint)
    {
        if (codePoint < 0x80)
        {
            return 1;
        }
        if (codePoint < 0x800)
        {
            return 2;
        }
        if (codePoint < 0x10000)
        {
            return 3;
        }
        return 4;
    }

private:
    static bool IsValidUtf8Char(const std::string& str)
    {
        if (str.empty() || str.size() > 4)
        {
            return false;
        }
        const auto first = static_cast<unsigned char>(str[0]);

        if ((first & 0x80) == 0)
        {
            return str.size() == 1;
        }
        if ((first & 0xE0) == 0xC0)
        {
            return str.size() == 2 && IsContinuationByte(str[1]);
        }
        if ((first & 0xF0) == 0xE0)
        {
            return str.size() == 3 && IsContinuationByte(str[1]) && IsContinuationByte(str[2]);
        }
        if ((first & 0xF8) == 0xF0)
        {
            return str.size() == 4 && IsContinuationByte(str[1]) && IsContinuationByte(str[2]) &&
                   IsContinuationByte(str[3]);
        }
        return false;
    }

    static bool IsContinuationByte(const char c)
    {
        return (static_cast<unsigned char>(c) & 0xC0) == 0x80;
    }

private:
    DataType data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is, cait::Char& c)
{
    if (is.good())
    {
        std::string input;
        std::getline(is, input);
        c = input;
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const cait::Char& c)
{
    os << c.data();
    return os;
}

inline cait::Char operator""_char(const char* str, const std::size_t)
{
    return cait::Char{str};
}

#endif // CAITLYN_CORE_CHAR_CHAR_H_
