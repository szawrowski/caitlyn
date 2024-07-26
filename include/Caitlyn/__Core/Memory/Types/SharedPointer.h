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

#ifndef CAITLYN_CORE_MEMORY_TYPES_SHAREDPOINTER_H
#define CAITLYN_CORE_MEMORY_TYPES_SHAREDPOINTER_H

#include <atomic>
#include <stdexcept>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
class SharedPtr
{
public:
    using ValueType = T;
    using Pointer = T*;
    using Reference = T&;
    using Counter = std::atomic_size_t;

public:
    SharedPtr() = default;

    SharedPtr(Pointer data) : data_{data}, ref_count_{data ? new Counter(1) : nullptr}
    {
    }

    SharedPtr(const SharedPtr& other) : data_{other.data_}, ref_count_{other.ref_count_}
    {
        ref_count_->fetch_add(1, std::memory_order_relaxed);
    }

    SharedPtr(SharedPtr&& other) noexcept : data_{other.data_}, ref_count_{other.ref_count_}
    {
        other.data_ = nullptr;
        other.ref_count_ = nullptr;
    }

    ~SharedPtr()
    {
        Release();
    }

public:
    SharedPtr& operator=(Pointer data)
    {
        reset(data);
        return *this;
    }

    SharedPtr& operator=(const SharedPtr& other)
    {
        if (this != &other)
        {
            Release();
            data_ = other.data_;
            ref_count_ = other.ref_count_;
            if (ref_count_)
            {
                ref_count_->fetch_add(1);
            }
        }
        return *this;
    }

    SharedPtr& operator=(SharedPtr&& other) noexcept
    {
        if (this != &other)
        {
            Release();
            data_ = other.data_;
            ref_count_ = other.ref_count_;
            other.data_ = nullptr;
            other.ref_count_ = nullptr;
        }
        return *this;
    }

public:
    Reference operator*() const
    {
        if (data_ == nullptr)
        {
            throw std::runtime_error{"Dereferencing null pointer."};
        }
        return *data_;
    }

    Pointer operator->() const
    {
        if (data_ == nullptr)
        {
            throw std::runtime_error{"Dereferencing null pointer."};
        }
        return data_;
    }

public:
    Pointer Get() const
    {
        return data_;
    }

public:
    bool operator==(const SharedPtr& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const SharedPtr& other) const
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
    void Reset(Pointer data = nullptr)
    {
        if (data_ != data)
        {
            Release();
            data_ = data;
            ref_count_ = data ? new Counter(1) : nullptr;
        }
    }

private:
    void Release() const
    {
        if (ref_count_ && ref_count_->fetch_sub(1, std::memory_order_relaxed) == 0)
        {
            delete data_;
            delete ref_count_;
        }
    }

private:
    Pointer data_{};
    Counter* ref_count_{};
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_MEMORY_TYPES_SHAREDPOINTER_H
