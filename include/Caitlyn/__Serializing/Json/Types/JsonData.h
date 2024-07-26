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

#ifndef CAITLYN_SERIALIZING_JSON_TYPES_DATA_H_
#define CAITLYN_SERIALIZING_JSON_TYPES_DATA_H_

#include <algorithm>
#include <deque>
#include <sstream>
#include <stdexcept>
#include <string>
#include <type_traits>
#include <utility>
#include <vector>

#include "Caitlyn/__Core/String.h"
#include "Caitlyn/__Serializing/Json/Types/JsonClass.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_JSON_NAMESPACE_BEGIN
__CAITLYN_DETAIL_NAMESPACE_BEGIN

class JsonData
{
public:
    using ArrayType = std::deque<JsonData*>;
    using ObjectType = std::vector<std::pair<String, JsonData*>>;
    using StringType = String;
    using NullType = NullPtr;
    using FloatingType = Float;
    using IntegralType = Int64;
    using BooleanType = Bool;

public:
    JsonData() : type_{JsonClass::Null}
    {
        new (&data_.null_value) NullType(nullptr);
    }

    JsonData(const JsonData& other) : type_(other.type_)
    {
        CopyUnion(other);
    }

    JsonData(JsonData&& other) noexcept : type_(other.type_)
    {
        MoveUnion(std::move(other));
    }

    template <typename T>
    JsonData(T value, typename std::enable_if<std::is_same<T, BooleanType>::value>::type* = nullptr)
        : type_{JsonClass::Boolean}
    {
        new (&data_.boolean_value) BooleanType(value);
    }

    template <typename T>
    JsonData(
        T value,
        typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, BooleanType>::value>::type* = nullptr)
        : type_{JsonClass::Integral}
    {
        new (&data_.integral_value) IntegralType(value);
    }

    template <typename T>
    JsonData(T value, typename std::enable_if<std::is_floating_point<T>::value>::type* = nullptr)
        : type_{JsonClass::Floating}
    {
        new (&data_.floating_value) FloatingType(value);
    }

    template <typename T>
    JsonData(T value, typename std::enable_if<std::is_convertible<T, std::string>::value>::type* = nullptr)
        : type_{JsonClass::String}
    {
        new (&data_.string_value) StringType(value);
    }

    ~JsonData()
    {
        DestroyUnion();
    }

public:
    JsonData& operator=(const JsonData& other)
    {
        if (this != &other)
        {
            DestroyUnion();
            type_ = other.type_;
            CopyUnion(other);
        }
        return *this;
    }

    JsonData& operator=(JsonData&& other) noexcept
    {
        if (this != &other)
        {
            DestroyUnion();
            type_ = other.type_;
            MoveUnion(std::move(other));
        }
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_same<T, BooleanType>::value, JsonData&>::type operator=(T value)
    {
        SetType(JsonClass::Boolean);
        data_.boolean_value = value;
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_integral<T>::value && !std::is_same<T, BooleanType>::value, JsonData&>::type
    operator=(T value)
    {
        SetType(JsonClass::Integral);
        data_.integral_value = value;
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_floating_point<T>::value, JsonData&>::type operator=(T value)
    {
        SetType(JsonClass::Floating);
        data_.floating_value = value;
        return *this;
    }

    template <typename T>
    typename std::enable_if<std::is_convertible<T, std::string>::value, JsonData&>::type operator=(T value)
    {
        SetType(JsonClass::String);
        data_.string_value = StringType(value);
        return *this;
    }

public:
    JsonData& operator[](const StringType& key)
    {
        SetType(JsonClass::Object);
        auto& object = data_.object_value;
        const auto it = std::find_if(
            object.begin(),
            object.end(),
            [&key](const std::pair<const StringType&, JsonData*>& pair) { return pair.first == key; });

        if (it == object.end())
        {
            object.emplace_back(key, new JsonData());
            return *object.back().second;
        }
        return *it->second;
    }

    JsonData& operator[](const SizeType index)
    {
        SetType(JsonClass::Array);
        auto& array = data_.array_value;
        if (index >= array.size())
        {
            array.resize(index + 1, nullptr);
        }
        if (!array[index])
        {
            new (array[index]) JsonData{};
        }
        return *array[index];
    }

public:
    JsonData& At(const StringType& key)
    {
        return operator[](key);
    }

    const JsonData& At(const StringType& key) const
    {
        const auto& object = data_.object_value;
        const auto it = std::find_if(
            object.begin(),
            object.end(),
            [&key](const std::pair<const StringType&, const JsonData*>& pair) { return pair.first == key; });

        if (it == object.end())
        {
            throw std::out_of_range{"Key not found"};
        }
        return *it->second;
    }

    JsonData& At(const SizeType index)
    {
        return operator[](index);
    }

    const JsonData& At(const SizeType index) const
    {
        return *data_.array_value.at(index);
    }

public:
    template <typename T>
    void Append(T arg)
    {
        if (type_ != JsonClass::Array)
        {
            SetType(JsonClass::Array);
        }
        data_.array_value.emplace_back(new JsonData{arg});
    }

    template <typename T, typename... Args>
    void Append(T arg, Args... args)
    {
        Append(arg);
        Append(std::forward<Args>(args)...);
    }

public:
    SizeType Size() const
    {
        if (type_ == JsonClass::Array)
        {
            return data_.array_value.size();
        }
        if (type_ == JsonClass::Object)
        {
            return data_.object_value.size();
        }
        return static_cast<SizeType>(-1);
    }

    SizeType Length() const
    {
        return Size();
    }

public:
    BooleanType HasMember(const StringType& key) const
    {
        if (type_ == JsonClass::Object)
        {
            const auto& object = data_.object_value;
            return std::find_if(
                       object.begin(),
                       object.end(),
                       [&key](const std::pair<const StringType&, const JsonData*>& pair)
                       { return pair.first == key; }) != object.end();
        }
        return false;
    }

    BooleanType IsNull() const
    {
        return type_ == JsonClass::Null;
    }

    BooleanType IsObject() const
    {
        return type_ == JsonClass::Object;
    }

    BooleanType IsArray() const
    {
        return type_ == JsonClass::Array;
    }

    BooleanType IsString() const
    {
        return type_ == JsonClass::String;
    }

    BooleanType IsFloating() const
    {
        return type_ == JsonClass::Floating;
    }

    BooleanType IsIntegral() const
    {
        return type_ == JsonClass::Integral;
    }

    BooleanType IsBoolean() const
    {
        return type_ == JsonClass::Boolean;
    }

public:
    ObjectType& GetData()
    {
        if (type_ != JsonClass::Object)
        {
            throw std::logic_error("Trying to access non-object types as object");
        }
        return data_.object_value;
    }

    JsonClass GetType() const
    {
        return type_;
    }

    StringType GetString() const
    {
        return IsString() ? data_.string_value : StringType{};
    }

    FloatingType GetFloating() const
    {
        return IsFloating() ? data_.floating_value : FloatingType{};
    }

    IntegralType GetIntegral() const
    {
        return IsIntegral() ? data_.integral_value : IntegralType{};
    }

    BooleanType GetBoolean() const
    {
        return IsBoolean() && data_.boolean_value;
    }

public:
    StringType ToString(const BooleanType mangling = false, const SizeType indent = 2) const
    {
        std::ostringstream oss;
        MakeOutput(oss, mangling, indent, indent);
        return oss.str();
    }

    static JsonData __internal_make(const JsonClass type)
    {
        JsonData obj;
        obj.SetType(type);
        return obj;
    }

private:
    void MakeOutput(
        std::ostringstream& oss, const BooleanType mangling, const SizeType base_indent, const SizeType indent) const
    {
        const StringType indent_str(indent, def::Space);

        switch (type_)
        {
            case JsonClass::Object:
            {
                oss << def::LeftCurlyBracket;
                const auto& object = data_.object_value;
                if (!object.empty())
                {
                    if (mangling)
                    {
                        oss << def::LineFeed;
                    }
                    BooleanType first = true;
                    for (const auto& member : object)
                    {
                        if (!first)
                        {
                            oss << def::Comma;
                            if (mangling)
                            {
                                oss << def::LineFeed;
                            }
                        }
                        if (mangling)
                        {
                            oss << indent_str;
                        }
                        oss << def::QuotationMark << member.first << def::QuotationMark << def::Colon;
                        if (mangling)
                        {
                            oss << def::Space;
                        }
                        member.second->MakeOutput(oss, mangling, base_indent, indent + base_indent);
                        first = false;
                    }
                    if (mangling)
                    {
                        oss << def::LineFeed;
                    }
                }
                if (mangling)
                {
                    oss << StringType(indent - base_indent, def::Space);
                }
                oss << def::RightCurlyBracket;
                break;
            }
            case JsonClass::Array:
            {
                oss << def::LeftSquareBracket;
                const auto& array = data_.array_value;
                if (!array.empty())
                {
                    if (mangling)
                    {
                        oss << def::LineFeed;
                    }
                    BooleanType first = true;
                    for (const auto& value : array)
                    {
                        if (!first)
                        {
                            oss << def::Comma;
                            if (mangling)
                            {
                                oss << def::LineFeed;
                            }
                        }
                        if (mangling)
                        {
                            oss << indent_str;
                        }
                        value->MakeOutput(oss, mangling, base_indent, indent + base_indent);
                        first = false;
                    }
                    if (mangling)
                    {
                        oss << def::LineFeed;
                    }
                }
                if (mangling)
                {
                    oss << StringType(indent - base_indent, def::Space);
                }
                oss << def::RightSquareBracket;
                break;
            }
            case JsonClass::String:
                oss << def::QuotationMark << data_.string_value << def::QuotationMark;
                break;
            case JsonClass::Floating:
                oss << data_.floating_value;
                break;
            case JsonClass::Integral:
                oss << data_.integral_value;
                break;
            case JsonClass::Boolean:
                oss << (data_.boolean_value ? String::ValueOf(true) : String::ValueOf(false));
                break;
            case JsonClass::Null:
                oss << String::ValueOf(nullptr);
                break;
            default:
                break;
        }
    }

    void CopyUnion(const JsonData& other)
    {
        switch (other.type_)
        {
            case JsonClass::Null:
                new (&data_.null_value) NullType(nullptr);
                break;
            case JsonClass::String:
                new (&data_.string_value) StringType(other.data_.string_value);
                break;
            case JsonClass::Floating:
                new (&data_.floating_value) FloatingType(other.data_.floating_value);
                break;
            case JsonClass::Integral:
                new (&data_.integral_value) IntegralType(other.data_.integral_value);
                break;
            case JsonClass::Boolean:
                new (&data_.boolean_value) BooleanType(other.data_.boolean_value);
                break;
            case JsonClass::Array:
                new (&data_.array_value) ArrayType();
                for (const auto* item : other.data_.array_value)
                {
                    data_.array_value.emplace_back(new JsonData{*item});
                }
                break;
            case JsonClass::Object:
                new (&data_.object_value) ObjectType();
                for (const auto& item : other.data_.object_value)
                {
                    data_.object_value.emplace_back(item.first, new JsonData{*item.second});
                }
                break;
            default:
                break;
        }
    }

    void MoveUnion(JsonData&& other)
    {
        switch (other.type_)
        {
            case JsonClass::Null:
                new (&data_.null_value) NullType{};
                break;
            case JsonClass::String:
                new (&data_.string_value) StringType{std::move(other.data_.string_value)};
                break;
            case JsonClass::Floating:
                new (&data_.floating_value) FloatingType(other.data_.floating_value);
                break;
            case JsonClass::Integral:
                new (&data_.integral_value) IntegralType(other.data_.integral_value);
                break;
            case JsonClass::Boolean:
                new (&data_.boolean_value) BooleanType(other.data_.boolean_value);
                break;
            case JsonClass::Array:
                new (&data_.array_value) ArrayType{std::move(other.data_.array_value)};
                break;
            case JsonClass::Object:
                new (&data_.object_value) ObjectType{std::move(other.data_.object_value)};
                break;
            default:
                break;
        }
        other.type_ = JsonClass::Null;
        new (&other.data_.null_value) NullType{};
    }

    void DestroyUnion()
    {
        switch (type_)
        {
            case JsonClass::Array:
                for (const auto* item : data_.array_value)
                {
                    delete item;
                }
                data_.array_value.~ArrayType();
                break;
            case JsonClass::Object:
                for (const auto& item : data_.object_value)
                {
                    delete item.second;
                }
                data_.object_value.~ObjectType();
                break;
            default:
                break;
        }
    }

    void SetType(const JsonClass type)
    {
        if (type_ != type)
        {
            DestroyUnion();
            type_ = type;
            switch (type)
            {
                case JsonClass::Null:
                    new (&data_.null_value) NullType(nullptr);
                    break;
                case JsonClass::String:
                    new (&data_.string_value) StringType();
                    break;
                case JsonClass::Floating:
                    new (&data_.floating_value) FloatingType();
                    break;
                case JsonClass::Integral:
                    new (&data_.integral_value) IntegralType();
                    break;
                case JsonClass::Boolean:
                    new (&data_.boolean_value) BooleanType();
                    break;
                case JsonClass::Array:
                    new (&data_.array_value) ArrayType();
                    break;
                case JsonClass::Object:
                    new (&data_.object_value) ObjectType();
                    break;
                default:
                    break;
            }
        }
    }

private:
    union DataUnion
    {
        ArrayType array_value;
        ObjectType object_value;
        StringType string_value;
        NullType null_value{};
        FloatingType floating_value;
        IntegralType integral_value;
        BooleanType boolean_value;

        DataUnion()
        {
        }

        ~DataUnion()
        {
        }
    } data_;

    JsonClass type_;
};

__CAITLYN_DETAIL_NAMESPACE_END

inline __detail::JsonData Make(const JsonClass value)
{
    return __detail::JsonData::__internal_make(value);
}

inline __detail::JsonData MakeObject()
{
    return Make(JsonClass::Object);
}

inline __detail::JsonData MakeArray()
{
    return Make(JsonClass::Array);
}

template <typename... Args>
__detail::JsonData MakeArray(Args... args)
{
    auto array = Make(JsonClass::Array);
    array.Append(std::forward<Args>(args)...);
    return array;
}

inline __detail::JsonData MakeNull()
{
    return Make(JsonClass::Null);
}

inline __detail::JsonData MakeString(const std::string& value)
{
    return __detail::JsonData{value};
}

inline __detail::JsonData MakeFloating(const __detail::JsonData::FloatingType value)
{
    return __detail::JsonData{std::to_string(value)};
}

inline __detail::JsonData MakeIntegral(const __detail::JsonData::IntegralType value)
{
    return __detail::JsonData{std::to_string(value)};
}

inline __detail::JsonData MakeBoolean(const __detail::JsonData::BooleanType value)
{
    return __detail::JsonData{std::to_string(value)};
}

__CAITLYN_JSON_NAMESPACE_END
__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_SERIALIZING_JSON_TYPES_DATA_H_
