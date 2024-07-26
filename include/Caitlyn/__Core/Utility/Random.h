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

#ifndef CAITLYN_CORE_UTILITY_RANDOM_H_
#define CAITLYN_CORE_UTILITY_RANDOM_H_

#include <chrono>
#include <limits>
#include <random>
#include <stdexcept>

#include "Caitlyn/__Base.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename T>
T Random(T min = std::numeric_limits<T>::min(), T max = std::numeric_limits<T>::max());

template <>
inline Int16 Random(const Int16 min, const Int16 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<Int16>{min, max}(engine);
}

template <>
inline UInt16 Random(const UInt16 min, const UInt16 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<UInt16>{min, max}(engine);
}

template <>
inline Int32 Random(const Int32 min, const Int32 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<Int32>{min, max}(engine);
}

template <>
inline UInt32 Random(const UInt32 min, const UInt32 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<UInt32>{min, max}(engine);
}

template <>
inline Int64 Random(const Int64 min, const Int64 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<Int64>{min, max}(engine);
}

template <>
inline UInt64 Random(const UInt64 min, const UInt64 max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_int_distribution<UInt64>{min, max}(engine);
}

template <>
inline Float Random(const Float min, const Float max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<Float>{min, max}(engine);
}

template <>
inline Double Random(const Double min, const Double max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<Double>{min, max}(engine);
}

template <>
inline Decimal Random(const Decimal min, const Decimal max)
{
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::uniform_real_distribution<Decimal>{min, max}(engine);
}

inline Bool RandomBoolean(const Double percentage = 0.5)
{
    if (percentage < 0.0 || percentage > 1.0)
    {
        throw std::invalid_argument{"True percentage is only 0.0..1.0"};
    }
    std::mt19937_64 engine(std::chrono::steady_clock::now().time_since_epoch().count());
    return std::bernoulli_distribution{percentage}(engine);
}

__CAITLYN_GLOBAL_NAMESPACE_END

#endif // CAITLYN_CORE_UTILITY_RANDOM_H_
