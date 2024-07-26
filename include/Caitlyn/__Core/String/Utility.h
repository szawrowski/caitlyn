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
        if (str[i] == def::ReverseSolidus && i + 1 < str.size())
        {
            if (str[i + 1] == def::QuotationMark)
            {
                oss << def::QuotationMark;
                ++i; // Skip the escaped character
            }
            else if (str[i + 1] == def::QuestionMark)
            {
                oss << def::QuestionMark;
                ++i;
            }
            else if (str[i + 1] == def::ReverseSolidus)
            {
                oss << def::ReverseSolidus;
                ++i;
            }
            else if (str[i + 1] == def::Solidus)
            {
                oss << def::Solidus;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterA)
            {
                oss << def::Bell;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterB)
            {
                oss << def::Backspace;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterF)
            {
                oss << def::FormFeed;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterN)
            {
                oss << def::LineFeed;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterR)
            {
                oss << def::CarriageReturn;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterT)
            {
                oss << def::CharacterTabulation;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterV)
            {
                oss << def::LineTabulation;
                ++i;
            }
            else if (str[i + 1] == def::LatinSmallLetterU)
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
                    oss << def::ReverseSolidus << str[i + 1];
                }
            }
            else
            {
                // Invalid escape sequence, handle it as an error
                oss << def::ReverseSolidus << str[i + 1];
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
