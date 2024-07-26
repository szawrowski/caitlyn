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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_

#include <fstream>

#include "Caitlyn/__Serializing/Json/Types/JsonParser.h"
#include "Caitlyn/__Serializing/Json/Utility.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

class JsonDocument
{
public:
    using ErrorType = Json::JsonError;
    using DataType = Json::__Detail::JsonData;
    using ParserType = Json::__Detail::JsonParser;

public:
    JsonDocument() = default;

    JsonDocument(const String& value)
    {
        Parse(value);
    }

    JsonDocument(const std::ifstream& stream)
    {
        Parse(stream);
    }

    JsonDocument(const JsonDocument& other) : root_{other.root_}, error_{other.error_}
    {
    }

    JsonDocument(JsonDocument&& other) noexcept : root_{std::move(other.root_)}, error_{other.error_}
    {
        other.root_ = Json::MakeNull();
        other.error_ = ErrorType::NoError;
    }

    ~JsonDocument() = default;

public:
    JsonDocument& operator=(const String& value)
    {
        Parse(value);
        return *this;
    }

    JsonDocument& operator=(const std::ifstream& stream)
    {
        Parse(stream);
        return *this;
    }

    JsonDocument& operator=(const JsonDocument& other)
    {
        if (this != &other)
        {
            root_ = other.root_;
            error_ = other.error_;
        }
        return *this;
    }

    JsonDocument& operator=(JsonDocument&& other) noexcept
    {
        if (this != &other)
        {
            root_ = std::move(other.root_);
            error_ = other.error_;
            other.root_ = Json::MakeNull();
            other.error_ = ErrorType::NoError;
        }
        return *this;
    }

public:
    DataType& operator[](const String& key)
    {
        return root_[key];
    }

    const DataType& operator[](const String& key) const
    {
        return root_.At(key);
    }

public:
    void Parse(const String& value)
    {
        const auto parser = ParserType::Parse(value);
        if (parser.HasError())
        {
            error_ = parser.GetError();
            root_ = Json::MakeNull();
        }
        else
        {
            error_ = ErrorType::NoError;
            root_ = parser.GetData();
        }
    }

    void Parse(const std::ifstream& ifs)
    {
        std::ostringstream buffer;
        buffer << ifs.rdbuf();
        Parse(buffer.str());
    }

    void AddMember(const String& key, const DataType& value)
    {
        root_[key] = value;
    }

    void RemoveMember(const String& key)
    {
        if (root_.HasMember(key))
        {
            auto& obj = root_.GetData();
            obj.erase(
                std::remove_if(
                    obj.begin(),
                    obj.end(),
                    [&key](const std::pair<const String&, const DataType*>& pair)
                    { return pair.first == key; }),
                obj.end());
        }
    }

    bool HasMember(const String& key) const
    {
        return root_.HasMember(key);
    }

    SizeType Size() const
    {
        return root_.Size();
    }

    bool HasError() const
    {
        return error_ != ErrorType::NoError;
    }

    ErrorType GetError() const
    {
        return error_;
    }

    String GetErrorString() const
    {
        return Json::GetErrorString(error_);
    }

    Json::JsonClass GetType() const
    {
        return root_.GetType();
    }

    String ToString(const bool mangling = false, const SizeType indent = 2) const
    {
        return root_.ToString(mangling, indent);
    }

private:
    DataType root_{Json::MakeObject()};
    ErrorType error_{ErrorType::NoError};
};

__CAITLYN_JSON_NAMESPACE_BEGIN

inline JsonDocument MakeDocument()
{
    return JsonDocument{};
}

inline JsonDocument MakeDocument(const String& value)
{
    return JsonDocument{value};
}

inline JsonDocument MakeDocument(const JsonDocument& value)
{
    return JsonDocument{value};
}

inline JsonDocument MakeDocument(JsonDocument&& value)
{
    return JsonDocument{std::move(value)};
}

inline JsonDocument MakeDocument(const std::ifstream& stream)
{
    return JsonDocument{stream};
}

__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

inline std::istream& operator>>(std::istream& is, Caitlyn::JsonDocument& value)
{
    std::ostringstream buffer;
    buffer << is.rdbuf();
    value.Parse(buffer.str());
    return is;
}

inline std::ostream& operator<<(std::ostream& os, const Caitlyn::JsonDocument& value)
{
    os << value.ToString();
    return os;
}

#endif // CAITLYN_SERIALIZING_JSON_TYPES_DOCUMENT_H_
