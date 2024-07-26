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

#ifndef CAITLYN_CORE_MEMORY_TYPES_RAWPOINTER_H_
#define CAITLYN_CORE_MEMORY_TYPES_RAWPOINTER_H_

#include <stdexcept>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
class Ptr final
{
public:
    using ValueType = T;
    using Pointer = T*;
    using Reference = T&;

public:
    Ptr() = default;

    Ptr(Pointer data) : data_{data}
    {
    }

    Ptr(const Ptr& other) : data_{other.data_}
    {
    }

public:
    Ptr& operator=(Pointer data)
    {
        this->data_ = data;
        return *this;
    }

    Ptr& operator=(const Ptr& other)
    {
        this->data_ = other.data_;
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
    bool operator==(const Ptr& other) const
    {
        return data_ == other.data_;
    }

    bool operator!=(const Ptr& other) const
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
    void Reset(Pointer new_data = nullptr)
    {
        delete data_;
        data_ = new_data;
    }

    void Destroy()
    {
        delete data_;
        data_ = nullptr;
    }

private:
    Pointer data_{};
};

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_MEMORY_TYPES_RAWPOINTER_H_
