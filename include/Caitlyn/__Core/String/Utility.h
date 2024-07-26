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

#ifndef CAITLYN_CORE_STRING_UTILITY_H_
#define CAITLYN_CORE_STRING_UTILITY_H_

#include <algorithm>
#include <sstream>

#include "Caitlyn/__Core/String/String.h"
#include "Caitlyn/__Core/Traits/Types/Base.h"
#include "Caitlyn/__Core/Traits/Types/Primary.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

inline std::vector<std::string> Split(const std::string& text, const char delim)
{
    std::stringstream ss{text};
    std::string item;
    std::vector<std::string> data;

    while (std::getline(ss, item, delim))
    {
        data.emplace_back(item);
    }
    return data;
}

inline std::string Repeat(const std::string& str, const size_t count)
{
    if (count < 2)
    {
        return str;
    }
    std::stringstream ss;
    for (size_t i = 0; i < count; ++i)
    {
        ss << str;
    }
    return ss.str();
}

inline String EscapeString(const String& str)
{
    std::ostringstream oss;

    for (size_t i = 0; i < str.size(); ++i)
    {
        if (str[i] == Def::ReverseSolidus && i + 1 < str.size())
        {
            if (str[i + 1] == Def::QuotationMark)
            {
                oss << Def::QuotationMark;
                ++i; // Skip the escaped character
            }
            else if (str[i + 1] == Def::QuestionMark)
            {
                oss << Def::QuestionMark;
                ++i;
            }
            else if (str[i + 1] == Def::ReverseSolidus)
            {
                oss << Def::ReverseSolidus;
                ++i;
            }
            else if (str[i + 1] == Def::Solidus)
            {
                oss << Def::Solidus;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterA)
            {
                oss << Def::Bell;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterB)
            {
                oss << Def::Backspace;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterF)
            {
                oss << Def::FormFeed;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterN)
            {
                oss << Def::LineFeed;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterR)
            {
                oss << Def::CarriageReturn;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterT)
            {
                oss << Def::CharacterTabulation;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterV)
            {
                oss << Def::LineTabulation;
                ++i;
            }
            else if (str[i + 1] == Def::LatinSmallLetterU)
            {
                if (i + 5 < str.size())
                {
                    auto hex = str.Substring(i + 2, 4).str();
                    // Convert the hexadecimal representation to a character
                    oss << static_cast<char>(std::stoi(hex, nullptr, 16));
                    i += 5; // Skip the escaped sequence
                }
                else
                {
                    // Incomplete escape sequence, handle it as an error
                    oss << Def::ReverseSolidus << str[i + 1];
                }
            }
            else
            {
                // Invalid escape sequence, handle it as an error
                oss << Def::ReverseSolidus << str[i + 1];
            }
        }
        else
        {
            oss << str[i];
        }
    }
    return oss.str();
}

inline bool IsNumber(const String& str)
{
    return str.NotEmpty() &&
           std::all_of(str.begin(), str.end(), [](const Char& c) { return IsDigit(c.GetCodePoint()); });
}

inline size_t FindFirstNonSpace(const String& str)
{
    for (size_t i = 0; i < str.size(); ++i)
    {
        if (!IsSpace(str[i].GetCodePoint()))
        {
            return i;
        }
    }
    return str.size();
}

inline size_t FindLastNonSpace(const String& str)
{
    for (size_t i = str.size() - 1; i > 0; --i)
    {
        if (!IsSpace(str[i].GetCodePoint()))
        {
            return i;
        }
    }
    return str.size();
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_STRING_UTILITY_H_
