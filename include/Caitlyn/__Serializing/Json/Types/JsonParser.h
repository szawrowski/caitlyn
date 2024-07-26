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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_

#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Serializing/Json/Types/JsonData.h"
#include "Caitlyn/__Serializing/Json/Types/JsonError.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

class JsonParser
{
public:
    static JsonParser Parse(const String& json)
    {
        JsonParser parser{json};

        if (json.IsEmpty())
        {
            parser.SetError(JsonError::InvalidJson);
            parser.SetErrorPosition(0);
            return parser;
        }
        const auto first = FindFirstNonSpace(json);
        const auto last = FindLastNonSpace(json);

        if (json[first] != def::LeftCurlyBracket)
        {
            parser.SetError(JsonError::InvalidJson);
            parser.SetErrorPosition(first);
            return parser;
        }
        if (json[last] != def::RightCurlyBracket)
        {
            parser.SetError(JsonError::InvalidJson);
            parser.SetErrorPosition(last);
            return parser;
        }
        parser.data_ = parser.ParseValue();
        return parser;
    }

    bool HasError() const
    {
        return error_ != JsonError::NoError;
    }

    JsonError GetError() const
    {
        return error_;
    }

    JsonData GetData() const
    {
        return data_;
    }

private:
    JsonParser(const String& json) : error_{JsonError::NoError}, json_{json}, position_{}
    {
    }

    JsonData ParseValue()
    {
        SkipSpace();

        if (position_ >= json_.size())
        {
            return JsonData{};
        }
        const auto current_char = json_[position_];

        if (current_char == def::QuotationMark)
        {
            return ParseString();
        }
        if (current_char == def::LeftCurlyBracket)
        {
            return ParseObject();
        }
        if (current_char == def::LeftSquareBracket)
        {
            return ParseArray();
        }
        if (current_char == def::LatinSmallLetterT || current_char == def::LatinSmallLetterF)
        {
            return ParseBoolean();
        }
        if (current_char == def::LatinSmallLetterN)
        {
            return ParseNull();
        }
        if (IsDigit(current_char.GetCodePoint()) || current_char == def::HyphenMinus || current_char == def::PlusSign)
        {
            return ParseNumber();
        }
        SetError(JsonError::UnexpectedCharacter);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseObject()
    {
        JsonData result = MakeObject();
        Next();
        SkipSpace();

        while (position_ < json_.size())
        {
            SkipSpace();

            if (json_[position_] == def::RightCurlyBracket)
            {
                Next();
                return result;
            }
            if (json_[position_] == def::QuotationMark)
            {
                Next();
                const auto key_end = json_.Find(def::QuotationMark, position_);

                if (key_end == String::NPosition)
                {
                    SetError(JsonError::UnterminatedString);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
                String key = json_.Substring(position_, key_end - position_);
                position_ = key_end + 1;

                SkipSpace();
                if (json_[position_] != def::Colon)
                {
                    SetError(JsonError::MissingColon);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
                Next();
                SkipSpace();
                result[key] = ParseValue();

                SkipSpace();
                if (json_[position_] == def::Comma)
                {
                    Next();
                    SkipSpace();

                    if (json_[position_] == def::RightCurlyBracket)
                    {
                        SetError(JsonError::TrailingComma);
                        SetErrorPosition(position_);
                        return JsonData{};
                    }
                }
                else if (json_[position_] == def::RightCurlyBracket)
                {
                    Next();
                    return result;
                }
                else
                {
                    SetError(JsonError::UnexpectedCharacter);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
            }
            else
            {
                SetError(JsonError::UnexpectedCharacter);
                SetErrorPosition(position_);
                return JsonData{};
            }
        }
        SetError(JsonError::UnterminatedObject);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseArray()
    {
        JsonData result = MakeArray();
        Next();
        SkipSpace();

        while (position_ < json_.size())
        {
            SkipSpace();

            if (json_[position_] == def::RightSquareBracket)
            {
                Next();
                return result;
            }
            const JsonData value = ParseValue();
            result.Append(value);

            SkipSpace();
            if (json_[position_] == def::Comma)
            {
                Next();
                SkipSpace();

                if (json_[position_] == def::RightSquareBracket)
                {
                    SetError(JsonError::TrailingComma);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
            }
            else if (json_[position_] == def::RightSquareBracket)
            {
                Next();
                return result;
            }
            else
            {
                SetError(JsonError::UnexpectedCharacter);
                errorPosition_ = position_;
                return JsonData{};
            }
        }
        SetError(JsonError::UnterminatedArray);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseNull()
    {
        if (json_.str().compare(position_, 4, String::ValueOf(nullptr)) == 0)
        {
            Next(4);
            return MakeNull();
        }
        SetError(JsonError::InvalidValue);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseString()
    {
        Next();
        std::ostringstream escaped_stream;

        while (position_ < json_.size() && json_[position_] != def::QuotationMark)
        {
            if (json_[position_] == def::ReverseSolidus)
            {
                Next();
                if (position_ >= json_.size())
                {
                    SetError(JsonError::UnterminatedString);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
                if (json_[position_] == def::QuotationMark)
                {
                    escaped_stream << def::QuotationMark;
                }
                else if (json_[position_] == def::ReverseSolidus)
                {
                    escaped_stream << def::ReverseSolidus;
                }
                else if (json_[position_] == def::LatinSmallLetterB)
                {
                    escaped_stream << def::Backspace;
                }
                else if (json_[position_] == def::LatinSmallLetterF)
                {
                    escaped_stream << def::FormFeed;
                }
                else if (json_[position_] == def::LatinSmallLetterN)
                {
                    escaped_stream << def::LineFeed;
                }
                else if (json_[position_] == def::LatinSmallLetterR)
                {
                    escaped_stream << def::CarriageReturn;
                }
                else if (json_[position_] == def::LatinSmallLetterT)
                {
                    escaped_stream << def::CharacterTabulation;
                }
                else if (json_[position_] == def::LatinSmallLetterU)
                {
                    if (position_ + 4 >= json_.size())
                    {
                        SetError(JsonError::InvalidEscapeSequence);
                        SetErrorPosition(position_);
                        return JsonData{};
                    }
                    String hex_code = json_.Substring(position_ + 1, 4);
                    try
                    {
                        const uint32_t code_point = std::stoul(hex_code.str(), nullptr, 16);
                        escaped_stream << static_cast<char>(code_point);
                    }
                    catch (const std::exception&)
                    {
                        SetError(JsonError::InvalidEscapeSequence);
                        SetErrorPosition(position_);
                        return JsonData{};
                    }
                    position_ += 4;
                }
                else
                {
                    SetError(JsonError::InvalidEscapeSequence);
                    SetErrorPosition(position_);
                    return JsonData{};
                }
                Next();
            }
            else
            {
                escaped_stream << json_[position_];
            }
            Next();
        }
        if (json_[position_] == def::QuotationMark)
        {
            Next();
            return escaped_stream.str();
        }
        SetError(JsonError::UnterminatedString);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseBoolean()
    {
        if (json_.str().compare(position_, 4, String::ValueOf(true)) == 0)
        {
            Next(4);
            return true;
        }
        if (json_.str().compare(position_, 5, String::ValueOf(false)) == 0)
        {
            Next(5);
            return false;
        }
        SetError(JsonError::InvalidValue);
        SetErrorPosition(position_);
        return JsonData{};
    }

    JsonData ParseNumber()
    {
        JsonData result;
        auto end_number = position_;
        while (end_number < json_.size() &&
               (IsDigit(json_[end_number].GetCodePoint()) || json_[end_number] == def::FullStop ||
                json_[end_number] == def::LatinSmallLetterE || json_[end_number] == def::LatinCapitalLetterE ||
                json_[end_number] == def::HyphenMinus || json_[end_number] == def::PlusSign))
        {
            ++end_number;
        }
        const String number_str = json_.Substring(position_, end_number - position_);
        try
        {
            if (number_str.Find(def::PlusSign) != String::NPosition ||
                number_str.Find(def::LatinSmallLetterE) != String::NPosition ||
                number_str.Find(def::LatinCapitalLetterE) != String::NPosition)
            {
                result = std::stod(number_str.str());
            }
            else
            {
                result = std::stoll(number_str.str());
            }
        }
        catch (const std::out_of_range&)
        {
            SetError(JsonError::OutOfRangeError);
            SetErrorPosition(position_);
            return JsonData{};
        }
        catch (const std::exception&)
        {
            SetError(JsonError::InvalidNumber);
            SetErrorPosition(position_);
            return JsonData{};
        }
        position_ = end_number;
        return result;
    }

    void SkipSpace()
    {
        while (position_ < json_.size() && IsSpace(json_[position_].GetCodePoint()))
        {
            Next();
        }
    }

    void Next(const SizeType count = 1)
    {
        position_ += count;
    }

    void SetError(const JsonError error)
    {
        error_ = error;
    }

    void SetErrorPosition(const SizeType position)
    {
        errorPosition_ = position;
    }

private:
    JsonData data_;
    JsonError error_;
    const String& json_;
    SizeType position_;
    SizeType errorPosition_;
};

__CAITLYN_DETAIL_NAMESPACE_END
__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_SERIALIZING_JSON_TYPES_PARSER_H_
