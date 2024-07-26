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

#ifndef CAITLYN_CORE_STRING_STRINGBUILDER_H_
#define CAITLYN_CORE_STRING_STRINGBUILDER_H_

#include "Caitlyn/__Core/String/String.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class StringBuilder
{
public:
    using data_type = std::ostringstream;

public:
    StringBuilder() = default;

    StringBuilder(const char str)
    {
        data_ << str;
    }

    StringBuilder(const char* str)
    {
        data_ << str;
    }

    StringBuilder(const String& str)
    {
        data_ << str;
    }

    template <typename... Args>
    StringBuilder(const String& str, Args&&... args)
    {
        data_ << String::Format(str, std::forward<Args>(args)...);
    }

    StringBuilder(const StringBuilder& other) : data_{other.data_.str()}
    {
    }

    StringBuilder(StringBuilder&& other) noexcept : data_{std::move(other.data_)}
    {
    }

public:
    void Append(const String& str)
    {
        data_ << str;
    }

    template <typename... Args>
    void Append(const String& str, Args&&... args)
    {
        data_ << String::Format(str, std::forward<Args>(args)...);
    }

    void AppendLine(const String& str)
    {
        data_ << str << Def::LineFeed;
    }

    template <typename... Args>
    void AppendLine(const String& str, Args&&... args)
    {
        data_ << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed;
    }

public:
    String str() const
    {
        return data_.str();
    }

private:
    data_type data_;
};

inline StringBuilder MakeText()
{
    return StringBuilder{};
}

inline StringBuilder MakeText(const char c)
{
    return StringBuilder{c};
}

inline StringBuilder MakeText(const String& str)
{
    return StringBuilder{str};
}

template <typename... Args>
StringBuilder MakeText(const String& str, Args&&... args)
{
    return StringBuilder{String::Format(str, std::forward<Args>(args)...)};
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_STRING_STRINGBUILDER_H_
