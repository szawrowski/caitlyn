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

#ifndef CAITLYN_CORE_IO_CONSOLE_H_
#define CAITLYN_CORE_IO_CONSOLE_H_

#include <iostream>

#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Core/Traits.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

inline void Write(const String& str)
{
    std::ios::sync_with_stdio(false);
    std::cout << str << std::flush;
}

template <typename T>
Required<Has_to_string<T>()> Write(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.to_string() << std::flush;
}

template <typename T>
Required<Has_str<T>()> Write(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.str() << std::flush;
}

template <typename T>
Required<ConvertibleToString<T>()> Write(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.ToString() << std::flush;
}

template <typename... Args>
void Write(const String& str, Args&&... args)
{
    std::ios::sync_with_stdio(false);
    std::cout << String::Format(str, std::forward<Args>(args)...) << std::flush;
}

inline void WriteLine()
{
    std::ios::sync_with_stdio(false);
    std::cout << Def::LineFeed << std::flush;
}

inline void WriteLine(const String& str)
{
    std::ios::sync_with_stdio(false);
    std::cout << str << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_to_string<T>()> WriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.to_string() << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_str<T>()> WriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.str() << Def::LineFeed << std::flush;
}

template <typename T>
Required<ConvertibleToString<T>()> WriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cout << value.ToString() << Def::LineFeed << std::flush;
}

template <typename... Args>
void WriteLine(const String& str, Args&&... args)
{
    std::ios::sync_with_stdio(false);
    std::cout << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
}

inline void ErrorWrite(const String& str)
{
    std::ios::sync_with_stdio(false);
    std::cerr << str << std::flush;
}

template <typename T>
Required<Has_to_string<T>()> ErrorWrite(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.to_string() << std::flush;
}

template <typename T>
Required<Has_str<T>()> ErrorWrite(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.str() << std::flush;
}

template <typename T>
Required<ConvertibleToString<T>()> ErrorWrite(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.ToString() << std::flush;
}

template <typename... Args>
void ErrorWrite(const String& str, Args&&... args)
{
    std::ios::sync_with_stdio(false);
    std::cerr << String::Format(str, std::forward<Args>(args)...) << std::flush;
}

inline void ErrorWriteLine(const String& str)
{
    std::ios::sync_with_stdio(false);
    std::cerr << str << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_to_string<T>()> ErrorWriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.to_string() << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_str<T>()> ErrorWriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.str() << Def::LineFeed << std::flush;
}

template <typename T>
Required<ConvertibleToString<T>()> ErrorWriteLine(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::cerr << value.ToString() << Def::LineFeed << std::flush;
}

template <typename... Args>
void ErrorWriteLine(const String& str, Args&&... args)
{
    std::ios::sync_with_stdio(false);
    std::cerr << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
}

inline void Log(const String& str)
{
    std::ios::sync_with_stdio(false);
    std::clog << str << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_to_string<T>()> Log(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::clog << value.to_string() << Def::LineFeed << std::flush;
}

template <typename T>
Required<Has_str<T>()> Log(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::clog << value.str() << Def::LineFeed << std::flush;
}

template <typename T>
Required<ConvertibleToString<T>()> Log(const T& value)
{
    std::ios::sync_with_stdio(false);
    std::clog << value.ToString() << Def::LineFeed << std::flush;
}

template <typename... Args>
void Log(const String& str, Args&&... args)
{
    std::ios::sync_with_stdio(false);
    std::clog << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed << std::flush;
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_IO_CONSOLE_H_