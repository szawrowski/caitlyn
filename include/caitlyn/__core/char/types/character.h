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

#ifndef CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_
#define CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

#include "caitlyn/__core/char/types/basic_character.h"
#include "caitlyn/__core/char/types/codepoint.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <>
class basic_character_t<char>
{
public:
    using value_type = char;
    using data_type = std::basic_string<value_type>;
    using size_type = data_type::size_type;
    using codepoint_type = codepoint_t;

public:
    basic_character_t() = default;

    basic_character_t(const char byte)
    {
        data_ = byte;
    }

    basic_character_t(const codepoint_type codepoint) : data_{from_code_point(codepoint)}
    {
    }

    basic_character_t(const char* bytes)
    {
        if (!is_valid_utf8_char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
    }

    basic_character_t(const data_type& bytes)
    {
        if (!is_valid_utf8_char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
    }

public:
    basic_character_t& operator=(const char byte)
    {
        data_ = byte;
        return *this;
    }

    basic_character_t& operator=(const codepoint_t codepoint)
    {
        data_ = from_code_point(codepoint);
        return *this;
    }

    basic_character_t& operator=(const char* bytes)
    {
        if (!is_valid_utf8_char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
        return *this;
    }

    basic_character_t& operator=(const data_type& bytes)
    {
        if (!is_valid_utf8_char(bytes))
        {
            throw std::invalid_argument("Invalid UTF-8 character");
        }
        data_ = bytes;
        return *this;
    }

    size_type size() const
    {
        return data_.size();
    }

    size_type length() const
    {
        return data_.size();
    }

    const char* data() const
    {
        return data_.data();
    }

    const char* c_str() const
    {
        return data_.c_str();
    }

    const char* str() const
    {
        return data_.data();
    }

    bool is_empty() const
    {
        return data_.empty();
    }

    bool not_empty() const
    {
        return !data_.empty();
    }

    bool operator>(const basic_character_t& other) const
    {
        return data_ > other.data_;
    }

    bool operator<(const basic_character_t& other) const
    {
        return data_ < other.data_;
    }

    bool operator>=(const basic_character_t& other) const
    {
        return data_ >= other.data_;
    }

    bool operator<=(const basic_character_t& other) const
    {
        return data_ <= other.data_;
    }

    bool operator==(const basic_character_t& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const basic_character_t& other) const
    {
        return !(*this == other);
    }

public:
    codepoint_type get_codepoint() const
    {
        codepoint_type codepoint;
        const auto lead = static_cast<unsigned char>(data_[0]);

        if ((lead & 0x80) == 0)
        {
            codepoint = lead;
        }
        else if ((lead & 0xE0) == 0xC0)
        {
            codepoint = (lead & 0x1F) << 6;
            codepoint |= (static_cast<unsigned char>(data_[1]) & 0x3F);
        }
        else if ((lead & 0xF0) == 0xE0)
        {
            codepoint = (lead & 0x0F) << 12;
            codepoint |= (static_cast<unsigned char>(data_[1]) & 0x3F) << 6;
            codepoint |= (static_cast<unsigned char>(data_[2]) & 0x3F);
        }
        else if ((lead & 0xF8) == 0xF0)
        {
            codepoint = (lead & 0x07) << 18;
            codepoint |= (static_cast<unsigned char>(data_[1]) & 0x3F) << 12;
            codepoint |= (static_cast<unsigned char>(data_[2]) & 0x3F) << 6;
            codepoint |= (static_cast<unsigned char>(data_[3]) & 0x3F);
        }
        else
        {
            codepoint = 0;
        }
        return codepoint;
    }

private:
    static data_type from_code_point(const codepoint_type codepoint)
    {
        if (codepoint == 0x00)
        {
            return {};
        }
        const size_type length = calculat_length(codepoint);

        if (length == 1)
        {
            return data_type{static_cast<char>(codepoint)};
        }
        std::ostringstream oss;

        if (length == 2)
        {
            oss << static_cast<unsigned char>(0xC0 | (codepoint >> 6));
            oss << static_cast<unsigned char>(0x80 | (codepoint & 0x3F));
            return oss.str();
        }
        if (length == 3)
        {
            oss << static_cast<unsigned char>(0xE0 | (codepoint >> 12));
            oss << static_cast<unsigned char>(0x80 | ((codepoint >> 6) & 0x3F));
            oss << static_cast<unsigned char>(0x80 | (codepoint & 0x3F));
            return oss.str();
        }
        oss << static_cast<unsigned char>(0xF0 | (codepoint >> 18));
        oss << static_cast<unsigned char>(0x80 | ((codepoint >> 12) & 0x3F));
        oss << static_cast<unsigned char>(0x80 | ((codepoint >> 6) & 0x3F));
        oss << static_cast<unsigned char>(0x80 | (codepoint & 0x3F));
        return oss.str();
    }

    static size_type calculat_length(const codepoint_type codepoint)
    {
        if (codepoint < 0x80)
        {
            return 1;
        }
        if (codepoint < 0x800)
        {
            return 2;
        }
        if (codepoint < 0x10000)
        {
            return 3;
        }
        return 4;
    }

private:
    static bool is_valid_utf8_char(const std::string& str)
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
            return str.size() == 2 && is_continuation_byte(str[1]);
        }
        if ((first & 0xF0) == 0xE0)
        {
            return str.size() == 3 && is_continuation_byte(str[1]) && is_continuation_byte(str[2]);
        }
        if ((first & 0xF8) == 0xF0)
        {
            return str.size() == 4 && is_continuation_byte(str[1]) && is_continuation_byte(str[2]) &&
                   is_continuation_byte(str[3]);
        }
        return false;
    }

    static bool is_continuation_byte(const char c)
    {
        return (static_cast<unsigned char>(c) & 0xC0) == 0x80;
    }

private:
    data_type data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is, cait::basic_character_t<char>& str)
{
    if (is.good())
    {
        std::string input;
        std::getline(is, input);
        str = input;
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const cait::basic_character_t<char>& str)
{
    os << str.data();
    return os;
}

inline cait::basic_character_t<char> operator""_char(const char* str, const std::size_t)
{
    return cait::basic_character_t<char>{str};
}

#endif // CAITLYN_CORE_CHAR_TYPES_CHARACTER_H_
