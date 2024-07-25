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

#include "caitlyn/__core/string.h"

__CAITLYN_GLOBAL_NAMESPACE_BEGIN
__CAITLYN_ERROR_NAMESPACE_BEGIN

template <typename E>
class unexpected_t
{
public:
    explicit unexpected_t(E error) : error_{std::move(error)}
    {
    }

    const E& get() const noexcept
    {
        return error_;
    }

private:
    E error_;
};

__CAITLYN_ERROR_NAMESPACE_END

template <typename E>
error::unexpected_t<E> make_failure(E error)
{
    return error::unexpected_t<E>{error};
}

inline error::unexpected_t<basic_string_t<char>> make_failure(const char* error)
{
    return error::unexpected_t<basic_string_t<char>>{basic_string_t<char>{error}};
}

inline error::unexpected_t<basic_string_t<char>> make_failure(const basic_string_t<char>& error)
{
    return error::unexpected_t<basic_string_t<char>>{error};
}

__CAITLYN_GLOBAL_NAMESPACE_END

template <typename E>
bool operator==(const cait::error::unexpected_t<E>& lhs, const cait::error::unexpected_t<E>& rhs)
{
    return lhs.get() == rhs.get();
}

template <typename E>
bool operator!=(const cait::error::unexpected_t<E>& lhs, const cait::error::unexpected_t<E>& rhs)
{
    return !(lhs == rhs);
}

#endif //CAITLYN_CORE_ERROR_UNEXPECTED_H_
