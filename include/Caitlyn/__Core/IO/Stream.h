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

#ifndef CAITLYN_CORE_IO_STREAM_H_
#define CAITLYN_CORE_IO_STREAM_H_

#include <iostream>

#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Core/Traits.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class InputStream
{
public:
    static String ReadLine(const String& message = String::Empty())
    {
        if (message.NotEmpty())
        {
            std::cout << message << std::flush;
        }

        std::basic_string<char> input;
        std::getline(std::cin, input);

        return input;
    }

    template <typename... Args>
    static String ReadLine(const String& str, Args&&... args)
    {
        return ReadLine(String::Format(str, std::forward<Args>(args)...));
    }

    static Char ReadChar(const String& message = String::Empty())
    {
        return ReadLine(message)[0];
    }

    template <typename... Args>
    static Char ReadChar(const String& str, Args&&... args)
    {
        return ReadChar(String::Format(str, std::forward<Args>(args)...));
    }
};

class OutputStream
{
public:
    static void Write(const String& str)
    {
        std::cout << str << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> Write(const T& value)
    {
        std::cout << value.to_string() << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> Write(const T& value)
    {
        std::cout << value.str() << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> Write(const T& value)
    {
        std::cout << value.ToString() << std::flush;
    }

    template <typename... Args>
    static void Write(const String& str, Args&&... args)
    {
        std::cout << String::Format(str, std::forward<Args>(args)...) << std::flush;
    }

    static void WriteLine()
    {
        std::cout << Def::LineFeed << std::flush;
    }

    static void WriteLine(const String& str)
    {
        std::cout << str << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> WriteLine(const T& value)
    {
        std::cout << value.to_string() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> WriteLine(const T& value)
    {
        std::cout << value.str() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> WriteLine(const T& value)
    {
        std::cout << value.ToString() << Def::LineFeed << std::flush;
    }

    template <typename... Args>
    static void WriteLine(const String& str, Args&&... args)
    {
        std::cout << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
    }
};

class ErrorStream
{
public:
    static void Write(const String& str)
    {
        std::cerr << str << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> Write(const T& value)
    {
        std::cerr << value.to_string() << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> Write(const T& value)
    {
        std::cerr << value.str() << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> Write(const T& value)
    {
        std::cerr << value.ToString() << std::flush;
    }

    template <typename... Args>
    static void Write(const String& str, Args&&... args)
    {
        std::cerr << String::Format(str, std::forward<Args>(args)...) << std::flush;
    }

    static void WriteLine()
    {
        std::cerr << Def::LineFeed << std::flush;
    }

    static void WriteLine(const String& str)
    {
        std::cerr << str << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> WriteLine(const T& value)
    {
        std::cerr << value.to_string() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> WriteLine(const T& value)
    {
        std::cerr << value.str() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> WriteLine(const T& value)
    {
        std::cerr << value.ToString() << Def::LineFeed << std::flush;
    }

    template <typename... Args>
    static void WriteLine(const String& str, Args&&... args)
    {
        std::cerr << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
    }
};

class LogStream
{
public:
    static void Write(const String& str)
    {
        std::clog << str << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> Write(const T& value)
    {
        std::clog << value.to_string() << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> Write(const T& value)
    {
        std::clog << value.str() << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> Write(const T& value)
    {
        std::clog << value.ToString() << std::flush;
    }

    template <typename... Args>
    static void Write(const String& str, Args&&... args)
    {
        std::clog << String::Format(str, std::forward<Args>(args)...) << std::flush;
    }

    static void WriteLine()
    {
        std::clog << Def::LineFeed << std::flush;
    }

    static void WriteLine(const String& str)
    {
        std::clog << str << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasToString<T>()> WriteLine(const T& value)
    {
        std::clog << value.to_string() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<HasStr<T>()> WriteLine(const T& value)
    {
        std::clog << value.str() << Def::LineFeed << std::flush;
    }

    template <typename T>
    static Required<ConvertibleToString<T>()> WriteLine(const T& value)
    {
        std::clog << value.ToString() << Def::LineFeed << std::flush;
    }

    template <typename... Args>
    static void WriteLine(const String& str, Args&&... args)
    {
        std::clog << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
    }
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_IO_STREAM_H_
