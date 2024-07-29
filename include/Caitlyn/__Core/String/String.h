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

#ifndef CAITLYN_CORE_STRING_TYPES_STRING_H_
#define CAITLYN_CORE_STRING_TYPES_STRING_H_

#include <algorithm>
#include <bitset>
#include <iterator>
#include <sstream>
#include <stdexcept>
#include <string>
#include <utility>


#include "Caitlyn/__Base.h"
#include "Caitlyn/__Core/Char.h"
#include "Caitlyn/__Core/Traits/Constraints/String.h"
#include "Caitlyn/__Core/Traits/Types/Base.h"
#include "Caitlyn/__Core/Traits/Types/Primary.h"
#include "Caitlyn/__Core/Traits/Constraints/Primary.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class String
{
public:
    using ValueType = char;
    using CharType = Char;
    using DataType = std::vector<CharType>;
    using BasicString = std::basic_string<ValueType>;
    using DifferenceType = DataType::difference_type;
    using Iterator = DataType::iterator;
    using ConstIterator = DataType::const_iterator;
    using ReverseIterator = DataType::reverse_iterator;
    using ConstReverseIterator = DataType::const_reverse_iterator;

public:
    String() = default;

    String(const char* str)
    {
        while (*str)
        {
            data_.emplace_back(DecodeUtf8Char(str));
            // Move past the current UTF-8 character
            str += DecodeUtf8Char(str).size();
        }
    }

    // Constructor from basic_string
    String(const BasicString& str)
    {
        const char* cstr = str.c_str();
        while (*cstr)
        {
            data_.emplace_back(DecodeUtf8Char(cstr));
            // Move past the current UTF-8 character
            cstr += DecodeUtf8Char(cstr).size();
        }
    }

    // Constructor from std::vector<character>
    String(const std::vector<CharType>& chars) : data_(chars)
    {
    }

    // Constructor from SizeType and char
    String(const SizeType count, const char ch)
    {
        for (SizeType i = 0; i < count; ++i)
        {
            data_.emplace_back(BasicString(1, ch));
        }
    }

    String(const SizeType count, const Char& ch)
    {
        for (SizeType i = 0; i < count; ++i)
        {
            data_.emplace_back(ch);
        }
    }

    // Constructor from iterator range
    template <typename InputIt>
    String(InputIt first, InputIt last)
    {
        while (first != last)
        {
            data_.emplace_back(decode_utf8_char(&(*first)));
            ++first;
        }
    }

    // Copy constructor
    String(const String& other) : data_(other.data_)
    {
    }

    // Move constructor
    String(String&& other) noexcept : data_(std::move(other.data_))
    {
    }

    // Copy assignment operator
    String& operator=(const String& other)
    {
        if (this != &other)
        {
            data_ = other.data_;
        }
        return *this;
    }

    // Move assignment operator
    String& operator=(String&& other) noexcept
    {
        if (this != &other)
        {
            data_ = std::move(other.data_);
        }
        return *this;
    }

public:
    // Size
    SizeType size() const
    {
        return data_.size();
    }

    SizeType Length() const
    {
        return data_.size();
    }

    const CharType& operator[](const SizeType index) const
    {
        return data_[index];
    }

    CharType& operator[](const SizeType index)
    {
        return data_[index];
    }

    const CharType& At(const SizeType index) const
    {
        if (index >= size())
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[index];
    }

    CharType& At(const SizeType idx)
    {
        if (idx >= size())
        {
            throw std::out_of_range("Index out of range");
        }
        return data_[idx];
    }

public:
    Iterator begin()
    {
        return data_.begin();
    }

    Iterator end()
    {
        return data_.end();
    }

    ConstIterator begin() const
    {
        return data_.begin();
    }

    ConstIterator end() const
    {
        return data_.end();
    }

    ReverseIterator rbegin()
    {
        return data_.rbegin();
    }

    ReverseIterator rend()
    {
        return data_.rend();
    }

    ConstReverseIterator rbegin() const
    {
        return data_.rbegin();
    }

    ConstReverseIterator rend() const
    {
        return data_.rend();
    }

    ConstIterator cbegin() const
    {
        return data_.cbegin();
    }

    ConstIterator cend() const
    {
        return data_.cend();
    }

    ConstReverseIterator crbegin() const
    {
        return data_.crbegin();
    }

    ConstReverseIterator crend() const
    {
        return data_.crend();
    }

public:
    String& operator+=(const String& str)
    {
        data_.insert(data_.end(), str.data_.begin(), str.data_.end());
        return *this;
    }

    String operator+(const String& str) const
    {
        DataType ret(data_.size() + str.data_.size());
        SizeType pos = 0;

        for (; pos < data_.size(); ++pos)
        {
            ret[pos] = data_[pos];
        }
        for (SizeType i = 0; i < str.data_.size(); ++i)
        {
            ret[pos + i] = str.data_[i];
        }
        return String{ret};
    }

    // Append character
    void PushBack(const CharType& c)
    {
        data_.push_back(c);
    }

    void Append(const char* cstr)
    {
        while (*cstr)
        {
            data_.emplace_back(DecodeUtf8Char(cstr));
            // Move past the current UTF-8 character
            cstr += DecodeUtf8Char(cstr).size();
        }
    }

    void Append(const SizeType count, const char* pattern)
    {
        SizeType i = 0;
        while (i < count)
        {
            data_.emplace_back(pattern);
            ++i;
        }
    }

    void Append(const SizeType count, const CharType& pattern)
    {
        SizeType i = 0;
        while (i < count)
        {
            data_.emplace_back(pattern);
            ++i;
        }
    }

    void Clear()
    {
        data_.clear();
    }

    bool operator>(const char* other) const
    {
        return str() > other;
    }

    bool operator<(const char* other) const
    {
        return str() < other;
    }

    bool operator>=(const char* other) const
    {
        return str() >= other;
    }

    bool operator<=(const char* other) const
    {
        return str() <= other;
    }

    bool operator==(const char* other) const
    {
        return str() == other;
    }

    bool operator!=(const char* other) const
    {
        return str() != other;
    }

    bool operator>(const String& other) const
    {
        return data_ > other.data_;
    }

    bool operator<(const String& other) const
    {
        return data_ < other.data_;
    }

    bool operator>=(const String& other) const
    {
        return data_ >= other.data_;
    }

    bool operator<=(const String& other) const
    {
        return data_ <= other.data_;
    }

    bool operator==(const String& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const String& other) const
    {
        return !(*this == other);
    }

    // Method to check if the string starts with a given prefix
    bool StartsWith(const String& prefix) const
    {
        if (prefix.size() > size())
        {
            return false;
        }
        return std::equal(prefix.begin(), prefix.end(), data_.begin());
    }

    // Method to check if the string ends with a given suffix
    bool EndsWith(const String& suffix) const
    {
        if (suffix.size() > size())
        {
            return false;
        }
        return std::equal(suffix.rbegin(), suffix.rend(), data_.rbegin());
    }

    // Method to check if the string contains a given substring
    bool Contains(const String& substring) const
    {
        return std::search(data_.begin(), data_.end(), substring.begin(), substring.end()) != data_.end();
    }

    // Method to find the first occurrence of a substring
    SizeType Find(const String& substr, const SizeType pos = 0) const
    {
        const auto it =
            std::search(data_.begin() + static_cast<DifferenceType>(pos), data_.end(), substr.begin(), substr.end());
        return (it != data_.end()) ? std::distance(data_.begin(), it) : NPosition;
    }

    // Method to find the last occurrence of a substring
    SizeType ReverseFind(const String& substr, SizeType pos = NPosition) const
    {
        if (substr.size() > size())
        {
            return NPosition;
        }
        if (pos >= size())
        {
            pos = size() - 1;
        }
        const auto it = std::search(
            data_.rbegin() + static_cast<DifferenceType>(size() - pos - 1),
            data_.rend(),
            substr.rbegin(),
            substr.rend());
        return (it != data_.rend()) ? size() - 1 - std::distance(data_.rbegin(), it) : NPosition;
    }

    // Substring method
    String Substring(const SizeType pos, const SizeType count = NPosition) const
    {
        if (pos > size())
        {
            throw std::out_of_range("Position out of range");
        }
        return String{std::vector<CharType>(
            data_.begin() + static_cast<DifferenceType>(pos),
            data_.begin() + static_cast<DifferenceType>(pos + std::min(count, size() - pos)))};
    }

    // Byte count method
    SizeType ByteCount() const
    {
        SizeType count = 0;
        for (const auto& ch : data_)
        {
            count += ch.size();
        }
        return count;
    }

    // Find_if method
    template <typename Predicate>
    SizeType FindIf(Predicate pred, const SizeType pos = 0) const
    {
        auto it = std::find_if(data_.begin() + static_cast<DifferenceType>(pos), data_.end(), pred);
        return (it != data_.end()) ? std::distance(data_.begin(), it) : NPosition;
    }

    // Find_if_not method
    template <typename Predicate>
    SizeType FindIfNot(Predicate pred, const SizeType pos = 0) const
    {
        auto it = std::find_if_not(data_.begin() + static_cast<DifferenceType>(pos), data_.end(), pred);
        return (it != data_.end()) ? std::distance(data_.begin(), it) : NPosition;
    }

public:
    bool IsEmpty() const
    {
        return data_.empty();
    }

    bool NotEmpty() const
    {
        return !data_.empty();
    }

    DataType data() const
    {
        return data_;
    }

    std::basic_string<char> str() const
    {
        std::ostringstream oss;

        for (const auto& elem : data_)
        {
            oss << elem.data();
        }
        return oss.str();
    }

    // Insert method
    void Insert(const SizeType pos, const char* cstr)
    {
        if (pos > size())
        {
            throw std::out_of_range("Position out of range");
        }
        DataType temp_data;
        while (*cstr)
        {
            temp_data.emplace_back(DecodeUtf8Char(cstr));
            cstr += DecodeUtf8Char(cstr).size();
        }
        data_.insert(data_.begin() + static_cast<DifferenceType>(pos), temp_data.begin(), temp_data.end());
    }

    void Insert(const SizeType pos, const String& str)
    {
        if (pos > size())
        {
            throw std::out_of_range("Position out of range");
        }
        data_.insert(data_.begin() + static_cast<DifferenceType>(pos), str.data_.begin(), str.data_.end());
    }

    void Insert(const SizeType pos, const SizeType count, const CharType& ch)
    {
        if (pos > size())
        {
            throw std::out_of_range("Position out of range");
        }
        data_.insert(data_.begin() + static_cast<DifferenceType>(pos), count, ch);
    }

public:
    String ToUppercase() const
    {
        auto tmp = data_;
        for (auto& elem : tmp)
        {
            elem = ::Caitlyn::ToUppercase(elem.GetCodePoint());
        }
        return tmp;
    }

    String ToLowercase() const
    {
        auto tmp = data_;
        for (auto& elem : tmp)
        {
            elem = ::Caitlyn::ToLowercase(elem.GetCodePoint());
        }
        return tmp;
    }

public:
    static String Empty()
    {
        return "";
    }

public:
    template <typename T>
    static Required<IsBoolean<T>(), const char*> ValueOf(T value)
    {
        return value ? "true" : "false";
    }

    template <typename T>
    static Required<IsNullPointer<T>(), const char*> ValueOf(T)
    {
        return "null";
    }

public:
    static constexpr auto NPosition{static_cast<SizeType>(-1)};

public:
    template <typename... Args>
    static String Format(const String& formatter, Args&&... args)
    {
        const std::vector<String> arguments{Formatter::ToString(std::forward<Args>(args))...};

        std::ostringstream result;
        SizeType auto_index = 0;
        SizeType pos = 0;

        while (pos < formatter.size())
        {
            if (formatter[pos] == Def::LeftCurlyBracket)
            {
                if (pos + 1 < formatter.size() && formatter[pos + 1] == Def::LeftCurlyBracket)
                {
                    result << Def::LeftCurlyBracket;
                    pos += 2;
                }
                else
                {
                    const SizeType end = formatter.Find(Def::RightCurlyBracket, pos);
                    if (end == String::NPosition)
                    {
                        throw Formatter::FormatError{"Mismatched braces in format string"};
                    }
                    const auto spec = formatter.Substring(pos + 1, end - pos - 1);
                    SizeType arg_index = 0;
                    constexpr SizeType spec_begin = 0;

                    if (spec.NotEmpty() && IsDigit(spec[spec_begin].GetCodePoint()))
                    {
                        SizeType index_end = spec_begin;
                        while (index_end < spec.size() && IsDigit(spec[index_end].GetCodePoint()))
                        {
                            ++index_end;
                        }
                        try
                        {
                            arg_index = std::stoul(spec.Substring(spec_begin, index_end - spec_begin).str());
                        }
                        catch (const std::out_of_range&)
                        {
                            throw Formatter::FormatError{"Invalid argument index"};
                        }
                        if (arg_index > arguments.size() - 1)
                        {
                            throw Formatter::FormatError{"Argument index out of range"};
                        }
                        auto format_spec = spec.Substring(index_end);

                        if (!format_spec.IsEmpty())
                        {
                            if (format_spec[0] == Def::Colon)
                            {
                                auto parsed_spec = Formatter::MakeSpacifier(format_spec);
                                result << Formatter::Process(arguments[auto_index], parsed_spec).str();
                            }
                        }
                        else
                        {
                            result << arguments[arg_index].str();
                        }
                    }
                    else if (spec.NotEmpty() && spec[spec_begin] == Def::Colon)
                    {
                        auto parsed_spec = Formatter::MakeSpacifier(spec);
                        result << Formatter::Process(arguments[arg_index], parsed_spec).str();
                    }
                    else if (arguments.size() == 1)
                    {
                        result << arguments[0].str();
                    }
                    else if (arguments.size() > 1)
                    {
                        result << arguments[auto_index++].str();
                    }
                    else
                    {
                        throw Formatter::FormatError{"Missing argument index in format string"};
                    }
                    pos = end + 1;
                }
            }
            else if (formatter[pos] == Def::RightCurlyBracket)
            {
                if (pos + 1 < formatter.size() && formatter[pos + 1] == Def::RightCurlyBracket)
                {
                    result << Def::RightCurlyBracket;
                    pos += 2;
                }
                else
                {
                    throw Formatter::FormatError{"Single right curly bracket in format string"};
                }
            }
            else
            {
                result << formatter[pos++];
            }
        }
        return result.str();
    }

private:
    struct Formatter
    {
        enum class Alignment
        {
            Left,
            Right,
            Center,
        };

        enum class ValueType
        {
            String,
            Integral,
            Floating,
        };

        enum class Representation
        {
            Default,
            Binary,
            BinaryPrefixed,
            Octal,
            OctalPrefixed,
            Hex,
            HexPrefixed,
        };

        struct FormatSpecifier
        {
            Alignment align = Alignment::Left;
            SizeType width = 0;
            Char fill = Def::Space;
            Representation repr = Representation::Default;
            ValueType type = ValueType::String;
            Int32 precision = -1;
        };

        class FormatError final : public std::runtime_error
        {
        public:
            explicit FormatError(const String& message) : std::runtime_error(message.str())
            {
            }
        };

    public:
        static String ToString(const String& value)
        {
            return String{value};
        }

        template <typename T>
        static Required<IsInteger<T>(), String> ToString(const T& value)
        {
            return std::to_string(value);
        }

        template <typename T>
        static Required<IsFloating<T>(), String> ToString(const T& value)
        {
            return std::to_string(value);
        }

        template <typename T>
        static Required<IsCharacter<T>(), String> ToString(const T& value)
        {
            return std::to_string(value);
        }

        template <typename T>
        static Required<IsBoolean<T>(), String> ToString(const T& value)
        {
            return String::ValueOf(value);
        }

        template <typename T>
        static Required<HasToString<T>(), String> ToString(const T& value)
        {
            return value.to_string();
        }

        template <typename T>
        static Required<HasStr<T>(), String> ToString(const T& value)
        {
            return value.str();
        }

        template <typename T>
        static Required<ConvertibleToString<T>(), String> ToString(const T& value)
        {
            return value.ToString();
        }

    public:
        static void SetFill(const String& config, FormatSpecifier& spec, SizeType& pos)
        {
            spec.fill = config[pos++];
        }

        static void ParseAlignment(const String& config, FormatSpecifier& spec, SizeType& pos)
        {
            if (pos + 1 < config.size() &&
                (config[pos + 1] == Def::LessThanSign || config[pos + 1] == Def::GreaterThanSign ||
                 config[pos + 1] == Def::CircumflexAccent))
            {
                SetFill(config, spec, pos);

                if (config[pos] == Def::LessThanSign)
                {
                    spec.align = Alignment::Left;
                    ++pos;
                }
                else if (config[pos] == Def::GreaterThanSign)
                {
                    spec.align = Alignment::Right;
                    ++pos;
                }
                else if (config[pos] == Def::CircumflexAccent)
                {
                    spec.align = Alignment::Center;
                    ++pos;
                }
            }
            else if (config[pos] == Def::LessThanSign)
            {
                spec.align = Alignment::Left;
                ++pos;
            }
            else if (config[pos] == Def::GreaterThanSign)
            {
                spec.align = Alignment::Right;
                ++pos;
            }
            else if (config[pos] == Def::CircumflexAccent)
            {
                spec.align = Alignment::Center;
                ++pos;
            }
        }

        static void ParseWidth(const String& config, FormatSpecifier& spec, SizeType& pos)
        {
            if (pos < config.size() && IsDigit(config[pos].GetCodePoint()))
            {
                spec.width = std::stoul(config.Substring(pos).str());
                while (pos < config.size() && IsDigit(config[pos].GetCodePoint()))
                {
                    ++pos;
                }
            }
        }

        static void ParsePrecision(const String& config, FormatSpecifier& spec, SizeType& pos)
        {
            if (pos < config.size() && config[pos] == Def::FullStop)
            {
                ++pos;
                if (pos < config.size() && IsDigit(config[pos].GetCodePoint()))
                {
                    spec.precision = std::stoi(config.Substring(pos).str());
                    while (pos < config.size() && IsDigit(config[pos].GetCodePoint()))
                    {
                        ++pos;
                    }
                }
            }
        }

        static void ParseValueType(const String& config, FormatSpecifier& spec, SizeType& pos)
        {
            if (pos < config.size())
            {
                if (config[pos] == Def::LatinSmallLetterS)
                {
                    spec.type = ValueType::String;
                    ++pos;
                }
                else if (config[pos] == Def::LatinSmallLetterD)
                {
                    spec.type = ValueType::Integral;
                    ++pos;
                }
                else if (config[pos] == Def::LatinSmallLetterF)
                {
                    spec.type = ValueType::Floating;
                    ++pos;
                }
            }
        }

        static FormatSpecifier MakeSpacifier(const String& config)
        {
            FormatSpecifier spec;
            SizeType pos = 0;

            if (config[pos++] != Def::Colon)
            {
                throw FormatError{"Incorrect format specifier"};
            }
            ParseAlignment(config, spec, pos);
            ParseWidth(config, spec, pos);
            ParsePrecision(config, spec, pos);
            ParseValueType(config, spec, pos);

            return spec;
        }

    public:
        static void ProcessAlignment(String& value, const FormatSpecifier& spec)
        {
            if (value.size() >= spec.width)
            {
                return;
            }
            switch (spec.align)
            {
                case Alignment::Left:
                    value.Append(spec.width - value.size(), spec.fill);
                    break;
                case Alignment::Right:
                    value.Insert(0, spec.width - value.size(), spec.fill);
                    break;
                case Alignment::Center:
                {
                    const SizeType padding = spec.width - value.size();
                    value.Insert(0, padding / 2, spec.fill);
                    value.Append(padding - padding / 2, spec.fill);
                    break;
                }
            }
        }

        static void ProcessSpecifier(String& value, const FormatSpecifier& spec)
        {
            ProcessAlignment(value, spec);
        }

        static String ProcessString(const String& value, const FormatSpecifier& spec)
        {
            String result = value;
            ProcessSpecifier(result, spec);
            return result;
        }

        static String ProcessFloating(const String& value, const FormatSpecifier& spec)
        {
            std::ostringstream oss;
            const auto dot_index = value.Find(Def::FullStop);

            if (dot_index != NPosition)
            {
                oss << value.Substring(0, dot_index + 1).str();

                if (spec.precision > 0)
                {
                    const SizeType limit = dot_index + 1 + spec.precision;
                    SizeType index = dot_index + 1;

                    while (index < value.size() && IsDigit(value[index].GetCodePoint()) && index < limit)
                    {
                        oss << value[index];
                        ++index;
                    }
                    while (index < limit)
                    {
                        oss << Def::DigitZero;
                        ++index;
                    }
                }
            }
            else
            {
                oss << value.str();
                if (spec.precision > 0)
                {
                    oss << Def::FullStop;
                    for (SizeType i = 0; i < static_cast<SizeType>(spec.precision); ++i)
                    {
                        oss << Def::DigitZero;
                    }
                }
            }
            String result = oss.str();
            ProcessSpecifier(result, spec);
            return result;
        }

        static String ProcessIntegral(const String& value, const FormatSpecifier& spec)
        {
            String result = value;
            ProcessSpecifier(result, spec);
            return result;
        }

        static String Process(const String& value, const FormatSpecifier& spec)
        {
            const auto type = spec.type;

            switch (type)
            {
                case ValueType::Integral:
                    return ProcessIntegral(value, spec);
                case ValueType::Floating:
                    return ProcessFloating(value, spec);
                default:
                    return ProcessString(value, spec);
            }
        }
    };

private:
    static CharType DecodeUtf8Char(const char*& cstr)
    {
        SizeType len;
        const Byte c = *cstr;

        if ((c & 0x80) == 0)
        {
            len = 1;
        }
        else if ((c & 0xE0) == 0xC0)
        {
            len = 2;
        }
        else if ((c & 0xF0) == 0xE0)
        {
            len = 3;
        }
        else if ((c & 0xF8) == 0xF0)
        {
            len = 4;
        }
        else
        {
            throw std::runtime_error("Invalid UTF-8 sequence");
        }
        return CharType{BasicString(cstr, len)};
    }

private:
    DataType data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is, Caitlyn::String& str)
{
    if (is.good())
    {
        std::basic_string<char> input;
        std::getline(is, input);
        str = input;
    }
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Caitlyn::String& str)
{
    os << str.str();
    return os;
}

inline Caitlyn::String operator""_str(const char* str, const Caitlyn::SizeType)
{
    return Caitlyn::String{str};
}

#endif // CAITLYN_CORE_STRING_TYPES_STRING_H_
