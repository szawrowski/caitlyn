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

#ifndef CAITLYN_CORE_MEMORY_TYPES_WEAKPOINTER_H
#define CAITLYN_CORE_MEMORY_TYPES_WEAKPOINTER_H

#include "Caitlyn/__Core/Memory/Types/SharedPointer.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
class WeakPtr
{
public:
    using ValueType = T;
    using Pointer = T*;
    using Reference = T&;
    using Resource = SharedPtr<T>;

public:
    WeakPtr() : data_(nullptr)
    {
    }

    WeakPtr(const Resource& resource) : data_{resource}
    {
    }

    WeakPtr(const WeakPtr& other) : data_{other.data_}
    {
    }

    WeakPtr(WeakPtr&& other) noexcept : data_{std::move(other.data_)}
    {
    }

public:
    WeakPtr& operator=(const WeakPtr& other)
    {
        data_ = other.data_;
        return *this;
    }

    WeakPtr& operator=(const Resource& sp)
    {
        this->data_ = sp;
        return *this;
    }

    WeakPtr& operator=(WeakPtr&& other) noexcept
    {
        data_ = std::move(other.data_);
        return *this;
    }

public:
    Reference operator*() const
    {
        if (data_ == nullptr || !data_.Get())
        {
            throw std::runtime_error{"Dereferencing null or expired weak pointer."};
        }
        return *data_;
    }

    Pointer operator->() const
    {
        if (data_ == nullptr || !data_.Get())
        {
            throw std::runtime_error{"Dereferencing null or expired weak pointer."};
        }
        return data_.Get();
    }

public:
    bool operator==(const WeakPtr& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const WeakPtr& other) const
    {
        return data_ != other.data_;
    }

    bool operator==(NullPtr) const
    {
        return data_ == nullptr;
    }

    bool operator!=(NullPtr) const
    {
        return data_ != nullptr;
    }

public:
    Resource lock() const
    {
        if (data_ == nullptr || !data_.Get())
        {
            return Resource();
        }
        return data_;
    }

public:
    bool expired() const
    {
        return data_ == nullptr || !data_.Get();
    }

private:
    Resource data_;
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_MEMORY_TYPES_WEAKPOINTER_H
