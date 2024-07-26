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

#ifndef CAITLYN_CORE_ERROR_UNEXPECTED_H_
#define CAITLYN_CORE_ERROR_UNEXPECTED_H_

#include "Caitlyn/__Core/String.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN

template <typename E>
class Unexpected
{
public:
    explicit Unexpected(E error) : error_{std::move(error)}
    {
    }

    const E& Get() const noexcept
    {
        return error_;
    }

private:
    E error_;
};

template <typename E>
Unexpected<E> MakeError(E error)
{
    return Unexpected<E>{error};
}

inline Unexpected<String> MakeError(const char* error)
{
    return Unexpected<String>{String{error}};
}

inline Unexpected<String> MakeError(const String& error)
{
    return Unexpected<String>{error};
}

__CAITLYN_GLOBAL_NAMESPACE_END

template <typename E>
bool operator==(const cait::Unexpected<E>& lhs, const cait::Unexpected<E>& rhs)
{
    return lhs.Get() == rhs.Get();
}

template <typename E>
bool operator!=(const cait::Unexpected<E>& lhs, const cait::Unexpected<E>& rhs)
{
    return !(lhs == rhs);
}

#endif //CAITLYN_CORE_ERROR_UNEXPECTED_H_
