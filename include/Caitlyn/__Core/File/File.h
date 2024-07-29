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

#ifndef CAITLYN_CORE_FILE_FILE_STREAM_H_
#define CAITLYN_CORE_FILE_FILE_STREAM_H_

#include <fstream>
#include <utility>
#include <vector>

#include "Caitlyn/__Core/String.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class File
{
public:
    File() = default;

    File(const String& filename) : filename_{filename}
    {
        Open();
    }

    template <typename... Args>
    File(const String& str, Args&&... args)
        : filename_{String::Format(str, std::forward<Args>(args)...)}
    {
        Open();
    }

    File(const File& other) : filename_{other.filename_}
    {
        Open();
    }

    ~File()
    {
        Close();
    }

public:
    void Open()
    {
        if (GetFilename().empty())
        {
            throw std::ios_base::failure{"Filename is empty"};
        }
        file_.open(GetFilename(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
        if (!file_.is_open())
        {
            throw std::ios_base::failure{"Failed to open file for writing."};
        }
    }

    void Close()
    {
        if (file_.is_open())
        {
            file_.close();
        }
    }

    void Erase()
    {
        Close();
        std::ofstream clearFile{GetFilename(), std::ios::out | std::ios::trunc | std::ios::binary};
        if (!clearFile.is_open())
        {
            throw std::ios_base::failure{"Failed to open file for clearing."};
        }
        clearFile.close();
        Open();
    }

    bool IsEof() const
    {
        return file_.eof();
    }

    explicit operator bool() const noexcept
    {
        return !file_.eof();
    }

    void SetPosition(const std::streampos& position)
    {
        currentPosition_ = position;
        file_.clear();
        file_.seekg(currentPosition_, std::ios::beg);
        if (file_.fail())
        {
            throw std::ios_base::failure{"Failed to set position in the file."};
        }
    }

    std::streampos GetPosition() const
    {
        return currentPosition_;
    }

public:
    // Reading methods
    String Read()
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekg(0, std::ios::end);
        const std::streamsize size = file_.tellg();
        file_.seekg(0, std::ios::beg);

        std::vector<char> buffer(size);
        if (file_.read(buffer.data(), size))
        {
            return buffer.data();
        }
        return {};
    }

    String ReadLine(const char delim = Def::LineFeed[0])
    {
        if (!file_.is_open())
        {
            Open();
        }
        if (file_.eof())
        {
            return {};
        }
        if (file_.fail() || file_.bad())
        {
            throw std::ios_base::failure{"Stream error encountered before reading."};
        }
        file_.clear();
        file_.seekg(currentPosition_, std::ios::beg);

        std::ostringstream result;
        char ch;
        while (file_.get(ch))
        {
            if (ch == delim)
            {
                currentPosition_ = file_.tellg();
                return result.str();
            }
            result << ch;
        }
        if (file_.eof())
        {
            currentPosition_ = file_.tellg();
            return result.str();
        }
        if (file_.fail() || file_.bad())
        {
            throw std::ios_base::failure{"Stream failed while reading."};
        }
        return result.str();
    }

    void Write(const char* data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data;
        file_.flush();
    }

    void Write(const String& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data;
        file_.flush();
    }

    template <typename T>
    Required<HasToString<T>()> Write(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.to_string();
        file_.flush();
    }

    template <typename T>
    Required<HasStr<T>()> Write(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.str();
        file_.flush();
    }

    template <typename T>
    Required<ConvertibleToString<T>()> Write(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.ToString();
        file_.flush();
    }

    template <typename... Args>
    void Write(const String& str, Args&&... args)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << String::Format(str, std::forward<Args>(args)...);
        file_.flush();
    }

    void WriteLine(const char* data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data << Def::LineFeed;
        file_.flush();
    }

    void WriteLine(const String& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<HasToString<T>()> WriteLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.to_string() << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<HasStr<T>()> WriteLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.str() << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<ConvertibleToString<T>()> WriteLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << data.ToString() << Def::LineFeed;
        file_.flush();
    }

    template <typename... Args>
    void WriteLine(const String& str, Args&&... args)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_ << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed;
        file_.flush();
    }

    void Append(const char* data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data;
        file_.flush();
    }

    void Append(const String& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data;
        file_.flush();
    }

    template <typename T>
    Required<HasToString<T>()> Append(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.to_string();
        file_.flush();
    }

    template <typename T>
    Required<HasStr<T>()> Append(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.str();
        file_.flush();
    }

    template <typename T>
    Required<ConvertibleToString<T>()> Append(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.ToString();
        file_.flush();
    }

    template <typename... Args>
    void Append(const String& str, Args&&... args)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << String::Format(str, std::forward<Args>(args)...);
        file_.flush();
    }

    void AppendLine(const char* data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data << Def::LineFeed;
        file_.flush();
    }

    void AppendLine(const String& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<HasToString<T>()> AppendLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.to_string() << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<HasStr<T>()> AppendLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.str() << Def::LineFeed;
        file_.flush();
    }

    template <typename T>
    Required<ConvertibleToString<T>()> AppendLine(const T& data)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << data.ToString() << Def::LineFeed;
        file_.flush();
    }

    template <typename... Args>
    void AppendLine(const String& str, Args&&... args)
    {
        if (!file_.is_open())
        {
            Open();
        }
        file_.seekp(0, std::ios::end);
        file_ << String::Format(str, std::forward<Args>(args)...) << Def::LineFeed;
        file_.flush();
    }

private:
    std::basic_string<char> GetFilename() const
    {
        return filename_.str();
    }

private:
    String filename_;
    std::basic_fstream<char> file_;
    std::streampos currentPosition_{};
};

inline File MakeFile(const String& filename)
{
    return File{filename};
}

__CAITLYN_GLOBAL_NAMESPACE_END

inline Caitlyn::File operator""_file(const char* filename, const Caitlyn::SizeType)
{
    return Caitlyn::File{filename};
}

#endif // CAITLYN_CORE_FILE_FILE_STREAM_H_
